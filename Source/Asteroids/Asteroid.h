// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/Messanger.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

UCLASS()
class ASTEROIDS_API AAsteroid : public AActor
{
	GENERATED_BODY()

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* AsteroidMeshComponent;
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialize(EStartSides::START_SIDE startSide, ESizes::SIZE size);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	float MoveSpeed;
	ESizes::SIZE Size;
	EStartSides::START_SIDE StartSide;
	FVector MoveDirection;
	FVector rotationSpeed;
	FRotator rotation;
	float buffer;
};
