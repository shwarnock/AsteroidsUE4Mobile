// Copyright 1998-2019 Epic Games, Inc. All Rights Reserve

#include "AsteroidsProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine.h"

AAsteroidsProjectile::AAsteroidsProjectile() 
{
	SetActorTickEnabled(true);
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/Asteroids/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AAsteroidsProjectile::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AAsteroidsProjectile::Tick(float DeltaTime) 
{
	CheckForOffScreen();
}


void AAsteroidsProjectile::CheckForOffScreen() {

	FVector2D ScreenLocation = FVector2D::ZeroVector;
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FVector dir = FVector::ZeroVector;
	FVector projectileLocation = GetActorLocation();
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
		SetActorLocation(newLocation);
	}
	else if (ScreenLocation.X < -SCREEN_BUFFER)
	{
		playerController->DeprojectScreenPositionToWorld(MAX_SCREEN_WIDTH + SCREEN_BUFFER, ScreenLocation.Y, newLocation, dir);
		SetActorLocation(newLocation);
	}
	else if (ScreenLocation.Y > MAX_SCREEN_HEIGHT + SCREEN_BUFFER)
	{
		playerController->DeprojectScreenPositionToWorld(ScreenLocation.X, -SCREEN_BUFFER, newLocation, dir);
		SetActorLocation(newLocation);
	}
	else if (ScreenLocation.Y < -SCREEN_BUFFER)
	{
		playerController->DeprojectScreenPositionToWorld(ScreenLocation.X, MAX_SCREEN_HEIGHT + SCREEN_BUFFER, newLocation, dir);
		SetActorLocation(newLocation);
	}
}

void AAsteroidsProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	Destroy();
}