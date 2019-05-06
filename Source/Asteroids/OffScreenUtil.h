// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Object.h"
#include "OffScreenUtil.generated.h"

/**
 * Utility class for checking if an actor is off the screen
 */
UCLASS(Blueprintable)
class UOffScreenUtil : public UObject
{
public:
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Screen Check")
	static void UpdateActorLocationWhenOffScreen(AActor* actor);

	UFUNCTION(BlueprintCallable, Category = "Screen Check")
	static bool CheckForOffScreen(AActor* actor);

	static FVector2D GetScreenSize();

private:
	static void SetScreenSize();
	static FVector2D ScreenSize;
	static float ScreenBuffer;
};
