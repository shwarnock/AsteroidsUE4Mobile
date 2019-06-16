// Copyright 1998-2019 Epic Games, Inc. All Rights Reserve

#include "AsteroidsProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine.h"
#include "Utils/ScreenUtil.h"
#include "AsteroidsGameInstance.h"

AAsteroidsProjectile::AAsteroidsProjectile() 
{
	SetActorTickEnabled(true);
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/Asteroids/Meshes/Projectile/TwinStickProjectile.TwinStickProjectile"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
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
	InitialLifeSpan = 1.5f;
}

void AAsteroidsProjectile::Tick(float DeltaTime) 
{
	if (UScreenUtil::CheckForOffScreen(this))
	{
		DestroyProjectile();
	}
}

void AAsteroidsProjectile::DestroyProjectile()
{
	FMessage message = FMessage();
	message.intMessage = 1;
	messanger->BulletDestroyed(message);
	Destroy();
}

void AAsteroidsProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DestroyProjectile();
}

void AAsteroidsProjectile::BeginPlay()
{
	Super::BeginPlay();

	UAsteroidsGameInstance* gameInstance = (UAsteroidsGameInstance*)GetWorld()->GetGameInstance();
	messanger = gameInstance->GetMessanger();
}