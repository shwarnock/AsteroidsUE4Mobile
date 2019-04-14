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
#include "Engine.h"

const FName AAsteroidsPawn::MoveForwardBinding("MoveForward");
const FName AAsteroidsPawn::MoveRightBinding("MoveRight");
const FName AAsteroidsPawn::FireBinding("Fire");

AAsteroidsPawn::AAsteroidsPawn()
{	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/Asteroids/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	SetActorLocation(FVector::ZeroVector);
	
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/Asteroids/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Movement
	MoveSpeed = FVector::ZeroVector;

	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;
}

void AAsteroidsPawn::SetScreenSize()
{
	FVector2D Result = FVector2D(0, 0);

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize( /*out*/Result);	
	}

	MAX_SCREEN_HEIGHT = Result.Y;
	MAX_SCREEN_WIDTH = Result.X;
}

void AAsteroidsPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AAsteroidsPawn::FireShot);
}

void AAsteroidsPawn::HandleAcceleration(FVector direction, float DeltaSeconds)
{
	if (MoveSpeed.X < MaxSpeed.X && MoveSpeed.Y < MaxSpeed.Y)
	{	
		MoveSpeed.X += direction.X * .5;
		MoveSpeed.Y += direction.Y * .5;
	}
}

void AAsteroidsPawn::Tick(float DeltaSeconds)
{
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector direction = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);
	if (direction.SizeSquared() > 0.0f)
	{
		Rotation = direction.Rotation();
	}

	HandleAcceleration(direction, DeltaSeconds);

	// If non-zero size, move this actor
	if (MoveSpeed.SizeSquared() > 0.0f)
	{
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(MoveSpeed, Rotation, true, &Hit);
	}

	MoveSpeed.X -= MoveSpeed.X * .02;
	MoveSpeed.Y -= MoveSpeed.Y * .02;

	for (int i = bullets.Num() - 1; i >= 0; --i)
	{
		if (bullets[i]->IsPendingKill() || !bullets[i]->IsValidLowLevel())
		{
			bullets.RemoveAt(i);
		}
	}

	CheckForOffScreen();
}

void AAsteroidsPawn::CheckForOffScreen() {
	FVector projectileLocation = GetActorLocation();

	FVector2D ScreenLocation = FVector2D::ZeroVector;
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FVector dir = FVector::ZeroVector;
	playerController->ProjectWorldLocationToScreen(projectileLocation, ScreenLocation);

	FVector2D Result = FVector2D(0, 0);
	FVector newLocation = FVector::ZeroVector;

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize( /*out*/Result);
	}

	MAX_SCREEN_HEIGHT = Result.Y;
	MAX_SCREEN_WIDTH = Result.X;

	if (ScreenLocation.X > MAX_SCREEN_WIDTH + SCREEN_BUFFER)
	{
		playerController->DeprojectScreenPositionToWorld(-SCREEN_BUFFER, ScreenLocation.Y, newLocation, dir);
		newLocation.Z = 0.0f;
		SetActorLocation(newLocation);
	}
	else if (ScreenLocation.X < -SCREEN_BUFFER)
	{
		playerController->DeprojectScreenPositionToWorld(MAX_SCREEN_WIDTH + SCREEN_BUFFER, ScreenLocation.Y, newLocation, dir);
		newLocation.Z = 0.0f;
		SetActorLocation(newLocation);
	}
	else if (ScreenLocation.Y > MAX_SCREEN_HEIGHT + SCREEN_BUFFER)
	{
		playerController->DeprojectScreenPositionToWorld(ScreenLocation.X, -SCREEN_BUFFER, newLocation, dir);
		newLocation.Z = 0.0f;
		SetActorLocation(newLocation);
	}
	else if (ScreenLocation.Y < -SCREEN_BUFFER)
	{
		playerController->DeprojectScreenPositionToWorld(ScreenLocation.X, MAX_SCREEN_HEIGHT + SCREEN_BUFFER, newLocation, dir);
		newLocation.Z = 0.0f;
		SetActorLocation(newLocation);
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

