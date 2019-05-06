// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MessageStruct.h"
#include "AsteroidManager.generated.h"

UCLASS()
class ASTEROIDS_API AAsteroidManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroidManager();

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void Initialize();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	const int SCREEN_BUFFER = 40;

	FVector GetStartPos(EStartSides::START_SIDE side);

	void CreateAsteroid(FVector startPos, EStartSides::START_SIDE startSide, ESizes::SIZE size);

	UFUNCTION()
	void RespondAsteroidDestroyed(FMessage message);
};
