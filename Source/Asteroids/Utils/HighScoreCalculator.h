// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HighScoreStruct.h"
#include "HighScoreCalculator.generated.h"

/**
 * Utility class for setting high scores list
 */
UCLASS(Blueprintable)
class ASTEROIDS_API UHighScoreCalculator : public UObject
{
	GENERATED_BODY()
	
public:
	bool static IsNewHighScore(int newScore);

	UFUNCTION(BlueprintCallable, Category = "Save High Score")
	static void SetNewHighScores(FHighScore newHighScore);

private:
	static const int MAX_HIGH_SCORES = 5;
};
