// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Utils/Messanger.h"
#include "AsteroidsPawn.generated.h"

UCLASS(Blueprintable)
class AAsteroidsPawn : public APawn
{
	GENERATED_BODY()

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;

	/* The Smoke component*/
	UPROPERTY(VisibleAnywhere, Category = "ParticleEffect")
	class UParticleSystemComponent* SmokeComponent;

	/* The Fire Component */
	UPROPERTY(VisibleAnywhere, Category = "ParticleEffect")
	class UParticleSystemComponent* FireComponent;
	
	/* The Explosion Component */
	UPROPERTY(VisibleAnywhere, Category = "ParticleEffect")
	class UParticleSystemComponent* ExplosionComponent;

public:
	AAsteroidsPawn();

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

protected:
	virtual void BeginPlay() override;

private:
	bool isDead;
	float playerCurrentHealth;
	float playerMaxHealth;

	float playerCurrentShields;
	float playerMaxShields;
	float shieldRegenDelay;
	float shieldRegenTimer;
	bool shieldTimerActive;
	float shieldRegenRate;

	void RegenerateShields(float DeltaSeconds);

	const FVector MaxSpeed = FVector(1000.0, 1000.0, 0);

	const int MAX_BULLETS = 2;
	int currentBullets;

	void HandleAcceleration(FVector direction, float DeltaSeconds);

	/* Flag to control firing  */
	uint32 bCanFire : 1;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

	bool damageTimerActive;
	float damageTimeDelay;
	float currentDamageTimeDelay;

	UMessanger* messanger;

	int playerScore;

	UFUNCTION()
	void HandleBulletDestroyed(FMessage message);

	UFUNCTION()
	void HandleUpdatePlayerScore(FMessage message);

	UFUNCTION()
	void HandleHealthPackPickedUp(FMessage message);

	UFUNCTION()
	void DestroyPawn();

public:
	/** Returns ShipMeshComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
};