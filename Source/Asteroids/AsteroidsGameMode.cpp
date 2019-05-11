// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AsteroidsGameMode.h"
#include "AsteroidsPawn.h"
#include "Engine.h"

AAsteroidsGameMode::AAsteroidsGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AAsteroidsPawn::StaticClass();
}

void AAsteroidsGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GetWorld()->GetName() == FString("AsteroidsMap"))
	{
		FActorSpawnParameters SpawnInfo;
		asteroidManager = GetWorld()->SpawnActor<AAsteroidManager>(FVector(0, 0, 1000), FRotator(0, 0, 0), SpawnInfo);
		FTimerHandle UnusedHandle;

		FTimerDelegate TimerDel;
		TimerDel.BindUFunction(this, FName("InitializeAsteroidManager"));
		GetWorldTimerManager().SetTimer(UnusedHandle, TimerDel, 1.0f, false);
	}
}

void AAsteroidsGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AAsteroidsGameMode::InitializeAsteroidManager()
{
	asteroidManager->Initialize();
}