#pragma once

#include "HighScoreStruct.generated.h"

USTRUCT(BlueprintType)
struct FHighScore
{
	GENERATED_BODY()

public:

	inline FHighScore()
	{
		initials = FText();
		highScore = NULL;
	}

	inline FHighScore(FText initials, int score)
	{
		this->initials = initials;
		this->highScore = score;
	}

	UPROPERTY(BlueprintReadWrite)
	FText initials;

	UPROPERTY(BlueprintReadWrite)
	int highScore;
};