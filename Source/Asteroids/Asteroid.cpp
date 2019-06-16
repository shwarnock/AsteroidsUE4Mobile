// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "AsteroidsProjectile.h"
#include "Utils/ScreenUtil.h"
#include "AsteroidsGameInstance.h"

// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> AsteroidMesh(TEXT("/Game/Asteroids/Meshes/Asteroid/Asteroid.Asteroid"));
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

	FVector rotationDelta = rotationSpeed * DeltaTime;
	rotation.Add(rotationDelta.X, rotationDelta.Y, 0);
	SetActorRotation(rotation);
	UScreenUtil::UpdateActorLocationWhenOffScreen(this, buffer);
}

void AAsteroid::Initialize(EStartSides::START_SIDE startSide, ESizes::SIZE size)
{
	MoveSpeed = FMath::RandRange(5, 10);
	StartSide = startSide;
	Size = size;

	switch (Size)
	{
	float coefficient, scale;
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

		scale = FMath::RandRange(7.0, 9.0F);
		SetActorScale3D(FVector(scale));
		buffer = 75.0f;
		break;
	case ESizes::Medium:
		MoveDirection = FVector(FMath::RandRange(-1.0f, 1.0f), FMath::RandRange(-1.0f, 1.0f), 0);
		scale = FMath::RandRange(4.0f, 6.0f);
		SetActorScale3D(FVector(scale));
		buffer = 45.0f;
		break;
	case ESizes::Small:
		MoveDirection = FVector(FMath::RandRange(-1.0f, 1.0f), FMath::RandRange(-1.0f, 1.0f), 0);
		scale = FMath::RandRange(1.0f, 3.0f);
		SetActorScale3D(FVector(scale));
		buffer = 20.0f;
		break;
	}

	float speed = FMath::RandRange(20, 120);
	rotationSpeed = FVector(speed, 0, speed);
	rotation = FRotator(FMath::RandRange(0, 360), FMath::RandRange(0, 360), FMath::RandRange(0, 360));
}

void AAsteroid::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp->GetCollisionProfileName() == "Projectile")
	{
		FMessage message = FMessage();
		message.intMessage = 1;
		message.asteroidSizeMessage = Size;
		message.currentPosMessage = GetActorLocation();
		UAsteroidsGameInstance* gameInstance = (UAsteroidsGameInstance*)GetWorld()->GetGameInstance();
		gameInstance->GetMessanger()->AsteroidDestroyed(message);
		Destroy();
	}
}
