// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Utils/ScreenUtil.h"
#include "AsteroidsGameInstance.h"

// Sets default values
AHealthPack::AHealthPack()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> HealthPack(TEXT("/Game/Asteroids/Meshes/HealthPack/Health_Pack.Health_Pack"));
	// Create the mesh component
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HealthPack"));
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetStaticMesh(HealthPack.Object);
	StaticMeshComponent->SetCollisionProfileName(TEXT("Pickup"));
	StaticMeshComponent->SetWorldLocation(FVector::ZeroVector);
	StaticMeshComponent->BodyInstance.SetCollisionProfileName(TEXT("Pickup"));
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AHealthPack::OnHit);
}

// Called when the game starts or when spawned
void AHealthPack::BeginPlay()
{
	Super::BeginPlay();
	
	FVector2D ScreenSize = UScreenUtil::GetScreenSize();
	FVector2D SpawnLocation = FVector2D(FMath::RandRange(SpawnBuffer, ScreenSize.X - SpawnBuffer), FMath::RandRange(SpawnBuffer, ScreenSize.Y - SpawnBuffer));

	FVector WorldLocation = UScreenUtil::GetWorldPosFromScreenPos(SpawnLocation, this);
	SetActorLocation(WorldLocation);

	SetActorScale3D(FVector(.5, .5, .5));
}

void AHealthPack::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FName pro = OtherComp->GetCollisionProfileName();
	if (OtherComp->GetCollisionProfileName() == FName("Pawn"))
	{
		FMessage message = FMessage();
		message.floatMessage = HealthIncrease;
		UAsteroidsGameInstance* gameInstance = (UAsteroidsGameInstance*) this->GetWorld()->GetGameInstance();
		gameInstance->GetMessanger()->HealthPackPickedUp(message);
		Destroy();
	}
}