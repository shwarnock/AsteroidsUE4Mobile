// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "AsteroidsProjectile.h"
#include "OffScreenUtil.h"
#include "AsteroidsGameInstance.h"

// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> AsteroidMesh(TEXT("/Game/Asteroids/Meshes/Asteroid.Asteroid"));
	// Create the mesh component
	AsteroidMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AsteroidMesh"));
	RootComponent = AsteroidMeshComponent;
	AsteroidMeshComponent->SetCollisionProfileName(TEXT("Asteroid"));
	AsteroidMeshComponent->SetStaticMesh(AsteroidMesh.Object);
	AsteroidMeshComponent->BodyInstance.SetCollisionProfileName(TEXT("Asteroid"));
	AsteroidMeshComponent->OnComponentHit.AddDynamic(this, &AAsteroid::OnHit);
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	FVector Movement = MoveDirection * MoveSpeed + CurrentLocation;
	SetActorLocation(Movement);
	UOffScreenUtil::UpdateActorLocationWhenOffScreen(this);
}

void AAsteroid::Initialize(EStartSides::START_SIDE startSide, ESizes::SIZE size)
{
	MoveSpeed = FMath::RandRange(5, 10);
	StartSide = startSide;
	Size = size;

	switch (Size)
	{
	float coefficient;
	case ESizes::Large:
		coefficient = FMath::RandRange(-1.0f, 1.0f);
		switch (StartSide)
		{
		case EStartSides::Left:
			MoveDirection = FVector(FMath::RandRange(0.2f, 1.0f), coefficient, 0);
			break;
		case EStartSides::Right:
			MoveDirection = FVector(FMath::RandRange(-1.0f, -0.2f), coefficient, 0.0f);
			break;
		case EStartSides::Up:
			MoveDirection = FVector(coefficient, FMath::RandRange(0.2f, 1.0), 0);
			break;
		case EStartSides::Down:
			MoveDirection = FVector(coefficient, FMath::RandRange(-1.0f, -0.2f), 0);
			break;
		}

		SetActorScale3D(FVector(FMath::RandRange(5.0f, 7.0f), FMath::RandRange(5.0f, 7.0f), FMath::RandRange(5.0f, 7.0f)));
		break;
	case ESizes::Medium:
		MoveDirection = FVector(FMath::RandRange(-1.0f, 1.0f), FMath::RandRange(-1.0f, 1.0f), 0);
		SetActorScale3D(FVector(FMath::RandRange(3.0f, 5.0f), FMath::RandRange(3.0f, 5.0f), FMath::RandRange(3.0f, 5.0f)));
		break;
	case ESizes::Small:
		MoveDirection = FVector(FMath::RandRange(-1.0f, 1.0f), FMath::RandRange(-1.0f, 1.0f), 0);
		SetActorScale3D(FVector(FMath::RandRange(1.0f, 3.0f), FMath::RandRange(1.0f, 3.0f), FMath::RandRange(1.0f, 3.0f)));
		break;
	}
}

void AAsteroid::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp->GetCollisionProfileName() == "Projectile")
	{
		FMessage message = FMessage();
		message.asteroidSizeMessage = Size;
		message.currentPosMessage = GetActorLocation();
		message.intMessage = 1;

		UAsteroidsGameInstance* gameInstance = (UAsteroidsGameInstance*)GetWorld()->GetGameInstance();
		gameInstance->GetMessanger()->AsteroidDestroyed(message);
		Destroy();
	}
}
