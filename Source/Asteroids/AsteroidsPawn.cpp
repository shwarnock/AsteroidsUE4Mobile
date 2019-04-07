// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AsteroidsPawn.h"
#include "AsteroidsProjectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

const FName AAsteroidsPawn::MoveForwardBinding("MoveForward");
const FName AAsteroidsPawn::MoveRightBinding("MoveRight");
const FName AAsteroidsPawn::FireBinding("Fire");

AAsteroidsPawn::AAsteroidsPawn()
{	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->RelativeRotation = FRotator(-80.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	// Movement
	MoveSpeed = FVector::ZeroVector;

	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
}

void AAsteroidsPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AAsteroidsPawn::FireShot);
}

void AAsteroidsPawn::HandleRotation()
{
	
}

void AAsteroidsPawn::HandleAccelerate(FVector MoveDirection)
{
	
	if (MoveSpeed.X < MaxSpeed.X && MoveSpeed.Y < MaxSpeed.Y)
	{
		// Add to velocity vector (using minus for y because Direct2D uses 0,0 as the top-left corner instead of bottom-left)
		MoveSpeed.X += MoveDirection.X * 0.2;
		MoveSpeed.Y -= MoveDirection.Y * 0.2;
	}
}

void AAsteroidsPawn::HandleMovement(FVector MoveDirection, float DeltaSeconds)
{
	//Simplified Stokes Law
	MoveSpeed.X = MoveSpeed.X - MoveSpeed.X * 0.02;
	MoveSpeed.Y = MoveSpeed.Y - MoveSpeed.Y * 0.02;

	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		SetActorLocation(Movement);
	}
}

void AAsteroidsPawn::Tick(float DeltaSeconds)
{
	HandleRotation();

	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, 0, 0);

	HandleAccelerate(MoveDirection);

	HandleMovement(MoveDirection, DeltaSeconds);

	for (int i = bullets.Num() - 1; i >= 0; --i)
	{
		if (bullets[i]->IsPendingKill() || !bullets[i]->IsValidLowLevel())
		{
			bullets.RemoveAt(i);
		}
	}
}

void AAsteroidsPawn::FireShot()
{
	// If it's ok to fire again
	if (bullets.Num() < 2)
	{
		const FVector FireDirection = GetActorForwardVector();
		const FRotator FireRotation = FireDirection.Rotation();
		// Spawn projectile at an offset from this pawn
		const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile
			bullets.Add(World->SpawnActor<AAsteroidsProjectile>(SpawnLocation, FireRotation));
		}

		bCanFire = false;

		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AAsteroidsPawn::ShotTimerExpired, FireRate);

		// try and play the sound if specified
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		bCanFire = false;
	}
}

void AAsteroidsPawn::ShotTimerExpired()
{
	bCanFire = true;
}

