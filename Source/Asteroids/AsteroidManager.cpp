// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidManager.h"
#include "OffScreenUtil.h"
#include "Asteroid.h"
#include "AsteroidsGameInstance.h"

// Sets default values
AAsteroidManager::AAsteroidManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currentAsteroidCount = 0;
	spawnMultiplier = 0;
}

void AAsteroidManager::HandleAsteroidDestroyed(FMessage message)
{
	FVector AsteroidCurrentPos = message.currentPosMessage;
	ESizes::SIZE newAsteroidSize;

	FMessage scoreMessage = FMessage();
	switch (message.asteroidSizeMessage)
	{
	case ESizes::Large:
		scoreMessage.intMessage = 20 * spawnMultiplier;
		messanger->UpdatePlayerScore(scoreMessage);
		newAsteroidSize = ESizes::Medium;
		for (int k = 0; k < spawnMultiplier; ++k)
		{
			CreateAsteroid(AsteroidCurrentPos, EStartSides::None, newAsteroidSize);
		}
		break;
	case ESizes::Medium:
		scoreMessage.intMessage = 15 * spawnMultiplier;
		messanger->UpdatePlayerScore(scoreMessage);
		newAsteroidSize = ESizes::Small;
		for (int k = 0; k < spawnMultiplier; ++k)
		{
			CreateAsteroid(AsteroidCurrentPos, EStartSides::None, newAsteroidSize);
		}
		break;
	case ESizes::Small:
		scoreMessage.intMessage = 10 * spawnMultiplier;
		messanger->UpdatePlayerScore(scoreMessage);
		break;
	}

	currentAsteroidCount -= message.intMessage;

	if (currentAsteroidCount == 0)
	{
		SpawnLevelInitialAsteroids(spawnMultiplier + 1);
	}
}

void AAsteroidManager::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AAsteroidManager::Initialize(int currentLevel)
{
	UAsteroidsGameInstance* gameInstance = (UAsteroidsGameInstance*) GetWorld()->GetGameInstance();
	messanger = gameInstance->GetMessanger();
	messanger->OnAsteroidDestroyed.AddDynamic(this, &AAsteroidManager::HandleAsteroidDestroyed);
	SpawnLevelInitialAsteroids(currentLevel);
}

void AAsteroidManager::SpawnLevelInitialAsteroids(int currentLevel)
{
	spawnMultiplier = currentLevel;
	for (int i = 0; i < spawnMultiplier; ++i)
	{
		EStartSides::START_SIDE startSide = EStartSides::START_SIDE(rand() % 4);
		FVector StartPos = GetStartPos(startSide);
		CreateAsteroid(StartPos, startSide, ESizes::Large);
	}
}

FVector AAsteroidManager::GetStartPos(EStartSides::START_SIDE side)
{
	FVector2D ScreenSize = UOffScreenUtil::GetScreenSize();
	APlayerController* playerController = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);

	FVector NewLocation;
	FVector Dir;

	switch (side)
	{
	case EStartSides::Left:
		playerController->DeprojectScreenPositionToWorld(-SCREEN_BUFFER, rand() % (int) ScreenSize.Y, NewLocation, Dir);
		break;
	case EStartSides::Right:
		playerController->DeprojectScreenPositionToWorld(SCREEN_BUFFER + ScreenSize.X, rand() % (int)ScreenSize.Y, NewLocation, Dir);
		break;
	case EStartSides::Up:
		playerController->DeprojectScreenPositionToWorld(rand() % (int)ScreenSize.X, -SCREEN_BUFFER, NewLocation, Dir);
		break;
	case EStartSides::Down:
		playerController->DeprojectScreenPositionToWorld(rand() % (int)ScreenSize.X, SCREEN_BUFFER + ScreenSize.Y, NewLocation, Dir);
		break;
	}

	NewLocation.Z = 0;
	return NewLocation;
}

void AAsteroidManager::CreateAsteroid(FVector startPos, EStartSides::START_SIDE startSide, ESizes::SIZE size)
{
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<AAsteroid>(startPos, Rotation, SpawnInfo)->Initialize(startSide, size);
	currentAsteroidCount++;
}

