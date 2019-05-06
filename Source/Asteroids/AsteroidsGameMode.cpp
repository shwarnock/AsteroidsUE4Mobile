// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AsteroidsGameMode.h"
#include "AsteroidsPawn.h"

AAsteroidsGameMode::AAsteroidsGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AAsteroidsPawn::StaticClass();
	Messanger = NewObject<UMessanger>();
}

UMessanger* AAsteroidsGameMode::GetMessanger()
{
	return Messanger;
}

