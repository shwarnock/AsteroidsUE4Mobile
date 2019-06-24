// Fill out your copyright notice in the Description page of Project Settings.

#include "HighScoreCalculator.h"
#include "Kismet/GameplayStatics.h"
#include "HighScoreStruct.h"
#include "AsteroidsSaveGame.h"

bool UHighScoreCalculator::IsNewHighScore(int newHighScore)
{
	UAsteroidsSaveGame* savedGame = (UAsteroidsSaveGame*)UGameplayStatics::LoadGameFromSlot("SaveGame", 0);
	if (savedGame == NULL)
	{
		return true;
	}

	TArray<FHighScore> highScores = savedGame->highScores;
	if (highScores.Num() < MAX_HIGH_SCORES)
	{
		return true;
	}

	for (int i = 0; i < MAX_HIGH_SCORES; ++i)
	{
		if (newHighScore > highScores[i].highScore)
		{
			return true;
		}
	}

	return false;
}

void UHighScoreCalculator::SetNewHighScores(FHighScore newHighScore)
{
	UAsteroidsSaveGame* savedGame = (UAsteroidsSaveGame*)UGameplayStatics::LoadGameFromSlot("SaveGame", 0);
	if (savedGame == NULL)
	{
		savedGame = Cast<UAsteroidsSaveGame>(UGameplayStatics::CreateSaveGameObject(UAsteroidsSaveGame::StaticClass()));
		TArray<FHighScore> highScores;
		highScores.Add(newHighScore);
		savedGame->highScores = highScores;
		UGameplayStatics::SaveGameToSlot(savedGame, "SaveGame", 0);
		return;
	}
	TArray<FHighScore> highScores = savedGame->highScores;
	int scoreCount = highScores.Num();
	for (int i = 0; i < scoreCount; ++i)
	{
		if (newHighScore.highScore > highScores[i].highScore)
		{
			highScores.Insert(newHighScore, i);
		}
	}

	int newScoreCount = highScores.Num();
	if (newScoreCount == scoreCount)
	{
		highScores.Add(newHighScore);
	}

	if (newScoreCount > MAX_HIGH_SCORES)
	{
		highScores.RemoveAt(newScoreCount - 1);
	}

	savedGame->highScores = highScores;

	UGameplayStatics::SaveGameToSlot(savedGame, "SaveGame", 0);
}