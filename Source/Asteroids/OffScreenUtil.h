// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"

/**
 * Utility class for checking if an actor is off the screen
 */
class OffScreenUtil
{
private:
	static void SetScreenSize();
	static FVector2D GetScreenSize();
	static FVector2D ScreenSize;
	static float ScreenBuffer;
public:
	static void CheckForOffScreen(AActor* actor);
};
