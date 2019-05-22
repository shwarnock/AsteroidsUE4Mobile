// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Delegates/Delegate.h"
#include "MessageStruct.h"
#include "Messanger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDamageDealtDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAsteroidDestroyedDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBulletDestroyedDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdatePlayerScoreDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerScoreWasUpdatedDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDiedDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthPackDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateLevelDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFireButtonPressedDelegate);

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

	UPROPERTY()
	FFireButtonPressedDelegate OnFireButtonPressed;

	UPROPERTY()
	FBulletDestroyedDelegate OnBulletDestroyed;

	UPROPERTY()
	FUpdatePlayerScoreDelegate OnUpdatePlayerScore;

	UPROPERTY(BlueprintAssignable)
	FPlayerScoreWasUpdatedDelegate OnPlayerScoreWasUpdated;

	UPROPERTY(BlueprintAssignable)
	FHealthPackDelegate OnHealthPackPickedUp;

	UPROPERTY(BlueprintAssignable)
	FUpdateLevelDelegate OnLevelIsUpdated;

public:
	void UpdatePlayerHealth(FMessage message);
	void AsteroidDestroyed(FMessage message);
	void BulletDestroyed(FMessage message);
	void UpdatePlayerScore(FMessage message);
	void PlayerScoreWasUpdated(FMessage message);
	void PlayerDied(FMessage message);
	void HealthPackPickedUp(FMessage message);
	void UpdateLevel(FMessage message);

	UFUNCTION(BlueprintCallable)
	void FireShot();
};
