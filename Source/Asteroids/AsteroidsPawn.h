// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AsteroidsProjectile.h"
#include "AsteroidsPawn.generated.h"

UCLASS(Blueprintable)
class AAsteroidsPawn : public APawn
{
	GENERATED_BODY()

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;

public:
	AAsteroidsPawn();

	UPROPERTY(Category = Gameplay, BlueprintReadOnly)
	float playerCurrentHealth;
	
	UPROPERTY(Category = gameplay, BlueprintReadOnly)
	float playerMaxHealth;

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void DealDamage(float damageAmount);

	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite )
	FVector GunOffset;
	
	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float FireRate;

	/* The speed our ship moves around the level */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	FVector MoveSpeed;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	FRotator Rotation;

	/** Sound to play each time we fire */
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void FireShot();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// End Actor Interface

	/* Handler for the fire timer expiry */
	void ShotTimerExpired();

	// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireBinding;

private:
	const FVector MaxSpeed = FVector(1000.0, 1000.0, 0);

	const int MAX_BULLETS = 2;
	TArray<AAsteroidsProjectile*> bullets;

	void HandleAcceleration(FVector direction, float DeltaSeconds);

	/* Flag to control firing  */
	uint32 bCanFire : 1;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

	bool damageTimerActive;
	float damageTimeDelay;
	float currentDamageTimeDelay;

public:
	/** Returns ShipMeshComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
};