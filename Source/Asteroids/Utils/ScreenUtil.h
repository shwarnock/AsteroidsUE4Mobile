// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Object.h"
#include "ScreenUtil.generated.h"

/**
 * Utility class for checking if an actor is off the screen
 */
UCLASS(Blueprintable)
class UScreenUtil : public UObject
{
public:
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Screen Check")
	static void UpdateActorLocationWhenOffScreen(AActor* actor, float buffer);

	UFUNCTION(BlueprintCallable, Category = "Screen Check")
	static bool CheckForOffScreen(AActor* actor);

	static FVector2D GetScreenSize();

	static FVector GetWorldPosFromScreenPos(FVector2D ScreenPos, AActor* actor);

private:
	static void SetScreenSize();
	static FVector2D ScreenSize;

	static APlayerController* PlayerController;
};
