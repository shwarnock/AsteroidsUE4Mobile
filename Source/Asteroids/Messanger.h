// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Delegates/Delegate.h"
#include "Union.h"
#include "MessageStruct.h"
#include "Messanger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDamageDealtDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAsteroidDestroyedDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDiedDelegate);

UCLASS()
class ASTEROIDS_API UMessanger : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FDamageDealtDelegate OnDamageDealt;

	UPROPERTY()
	FAsteroidDestroyedDelegate OnAsteroidDestroyed;

	UPROPERTY(BlueprintAssignable)
	FPlayerDiedDelegate OnPlayerDied;

public:
	void UpdatePlayerHealth(FMessage message);
	void AsteroidDestroyed(FMessage message);
	void PlayerDied();
};
