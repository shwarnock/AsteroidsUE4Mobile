// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Messanger.h"
#include "GameFramework/GameModeBase.h"
#include "AsteroidsGameMode.generated.h"

UCLASS(MinimalAPI)
class AAsteroidsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAsteroidsGameMode();

	UFUNCTION(BlueprintCallable, Category = "Messanger")
	UMessanger* GetMessanger();

private:
	UMessanger* Messanger;
};



