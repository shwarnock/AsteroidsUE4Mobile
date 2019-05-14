// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MessageStruct.h"
#include "Messanger.h"
#include "AsteroidManager.generated.h"

UCLASS()
class ASTEROIDS_API AAsteroidManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroidManager();

	UFUNCTION()
	void Initialize(int currentLevel);

protected:
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

private:
	const int SCREEN_BUFFER = 40;

	void SpawnLevelInitialAsteroids(int currentLevel);

	int currentAsteroidCount;
	FVector GetStartPos(EStartSides::START_SIDE side);

	void CreateAsteroid(FVector startPos, EStartSides::START_SIDE startSide, ESizes::SIZE size);

	UFUNCTION()
	void HandleAsteroidDestroyed(FMessage message);

	int spawnMultiplier;

	UMessanger* messanger;
};
