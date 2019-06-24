#pragma once

#include "HighScoreStruct.generated.h"

USTRUCT(BlueprintType)
struct FHighScore
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	FText initials;

	UPROPERTY(BlueprintReadWrite)
	int highScore;
};