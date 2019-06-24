#include "AsteroidsPawn.h"
#include "AsteroidsProjectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Utils/MessageStruct.h"
#include "Utils/HighScoreCalculator.h"

#include "Utils/ScreenUtil.h"
#include "AsteroidsGameInstance.h"

const FName AAsteroidsPawn::MoveForwardBinding("MoveForward");
const FName AAsteroidsPawn::MoveRightBinding("MoveRight");

AAsteroidsPawn::AAsteroidsPawn()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/Asteroids/Meshes/PlayerPawn/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	ShipMeshComponent->SetWorldLocation(FVector::ZeroVector);
	ShipMeshComponent->BodyInstance.SetCollisionProfileName("Pawn");
	RootComponent->SetWorldLocation(FVector::ZeroVector);
	SetActorLocation(FVector::ZeroVector);
	ShipMeshComponent->OnComponentHit.AddDynamic(this, &AAsteroidsPawn::OnHit);

	//Smoke
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Smoke(TEXT("/Game/MobileStarterContent/Particles/P_Smoke.P_Smoke"));
	SmokeComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke"));
	SmokeComponent->SetupAttachment(ShipMeshComponent);
	SmokeComponent->SetTemplate(Smoke.Object);
	SmokeComponent->bAutoActivate = false;
	SmokeComponent->SetRelativeLocation(FVector(-30, 0, 30));
	FRotator rotation = SmokeComponent->GetComponentRotation();
	SmokeComponent->SetRelativeRotation(FRotator(180, 0, 180));

	//Fire
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Fire(TEXT("/Game/MobileStarterContent/Particles/P_Fire.P_Fire"));
	FireComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire"));
	FireComponent->SetupAttachment(ShipMeshComponent);
	FireComponent->SetTemplate(Fire.Object);
	FireComponent->bAutoActivate = false;
	FireComponent->SetRelativeLocation(FVector(-30, 0, 30));

	//Explosion
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Explosion(TEXT("/Game/MobileStarterContent/Particles/P_Explosion.P_Explosion"));
	ExplosionComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion"));
	ExplosionComponent->SetupAttachment(ShipMeshComponent);
	ExplosionComponent->SetTemplate(Explosion.Object);
	ExplosionComponent->bAutoActivate = false;

	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/Asteroids/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Movement
	MoveSpeed = FVector::ZeroVector;

	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;

	playerMaxHealth = 100.0f;
	playerCurrentHealth = 100.0f;

	playerMaxShields = 100.0f;
	playerCurrentShields = 100.0f;
	shieldRegenDelay = 6.0f;
	shieldRegenTimer = 0.0f;
	shieldRegenRate = 10.0f;
	shieldTimerActive = false;
	damageTimeDelay = 1;
	currentDamageTimeDelay = 0;
	damageTimerActive = false;

	currentBullets = 0;

	playerScore = 0;
}

void AAsteroidsPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);

	PlayerInputComponent->BindAction("FireBullet", IE_Pressed, this, &AAsteroidsPawn::FireShot);
}

void AAsteroidsPawn::HandleAcceleration(FVector direction, float DeltaSeconds)
{
	if (MoveSpeed.X < MaxSpeed.X && MoveSpeed.Y < MaxSpeed.Y)
	{	
		MoveSpeed.X += direction.X * .5;
		MoveSpeed.Y += direction.Y * .5;
	}
}

void AAsteroidsPawn::BeginPlay()
{
	Super::BeginPlay();

	UAsteroidsGameInstance* gameInstance = (UAsteroidsGameInstance*)GetWorld()->GetGameInstance();
	messanger = gameInstance->GetMessanger();
	messanger->OnFireButtonPressed.AddDynamic(this, &AAsteroidsPawn::FireShot);
	messanger->OnBulletDestroyed.AddDynamic(this, &AAsteroidsPawn::HandleBulletDestroyed);
	messanger->OnUpdatePlayerScore.AddDynamic(this, &AAsteroidsPawn::HandleUpdatePlayerScore);
	messanger->OnHealthPackPickedUp.AddDynamic(this, &AAsteroidsPawn::HandleHealthPackPickedUp);

	ExplosionComponent->DeactivateSystem();
}

void AAsteroidsPawn::HandleBulletDestroyed(FMessage message)
{
	currentBullets -= message.intMessage;
}

void AAsteroidsPawn::DestroyPawn()
{
	Destroy();
}

void AAsteroidsPawn::DealDamage(float damage)
{
	if (!damageTimerActive)
	{
		if (playerCurrentShields > 0.0f)
		{
			shieldRegenTimer = 0.0f;
			shieldTimerActive = true;
			playerCurrentShields -= damage;
			FMessage message;
			message.floatMessage = playerCurrentShields / playerMaxShields;
			message.typeMessage = EMessageTypes::Float;
			messanger->ShieldsUpdated(message);
			return;
		}

		playerCurrentHealth -= damage;

		if (playerCurrentHealth <= 0.0f)
		{
			if (UHighScoreCalculator::IsNewHighScore(playerScore))
			{
				FMessage message;
				message.intMessage = playerScore;
				messanger->NewHighScore(message);
			}
			else
			{
				FMessage message = FMessage();
				message.intMessage = playerScore;
				messanger->PlayerDied(message);
			}

			SmokeComponent->SetHiddenInGame(true);
			FireComponent->SetHiddenInGame(true);

			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle, 1.0f, false);

			APlayerController* playerController = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
			this->DisableInput(playerController);
			MoveSpeed = FVector::ZeroVector;
			ShipMeshComponent->SetHiddenInGame(true);

			ExplosionComponent->ActivateSystem();
			FTimerDelegate TimerDel;
			TimerDel.BindUFunction(this, FName("DestroyPawn"));
			GetWorldTimerManager().SetTimer(UnusedHandle, TimerDel, 1.0f, false);
		}
		else
		{
			shieldRegenTimer = 0.0f;
			shieldTimerActive = true;
			FMessage message = FMessage();
			message.floatMessage = playerCurrentHealth / playerMaxHealth;
			messanger->UpdatePlayerHealth(message);
		}

		if (playerCurrentHealth < 50.0f)
		{
			SmokeComponent->ActivateSystem();
		}

		if (playerCurrentHealth < 25.0f)
		{
			SmokeComponent->DeactivateSystem();
			FireComponent->ActivateSystem();
		}
	}
}

void AAsteroidsPawn::HandleUpdatePlayerScore(FMessage message)
{
	playerScore += message.intMessage;

	message.intMessage = playerScore;
	messanger->PlayerScoreWasUpdated(message);
}

void AAsteroidsPawn::Tick(float DeltaSeconds)
{
	if (damageTimerActive)
	{
		currentDamageTimeDelay += DeltaSeconds;
	}

	if (currentDamageTimeDelay >= damageTimeDelay)
	{
		damageTimerActive = false;
		currentDamageTimeDelay = 0;
	}

	if (shieldTimerActive)
	{
		shieldRegenTimer += DeltaSeconds;
	}
	else
	{
		RegenerateShields(DeltaSeconds);
	}

	if (shieldRegenTimer >= shieldRegenDelay)
	{
		shieldRegenTimer = 0.0f;
		shieldTimerActive = false;
	}
	
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector direction = FVector(ForwardValue, -RightValue, 0.f).GetClampedToMaxSize(1.0f);
	if (direction.SizeSquared() > 0.0f)
	{
		Rotation = direction.Rotation();
	}

	HandleAcceleration(direction, DeltaSeconds);

	// If non-zero size, move this actor
	if (MoveSpeed.SizeSquared() > 0.0f)
	{
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(MoveSpeed, Rotation, true, &Hit);
	}

	MoveSpeed.X -= MoveSpeed.X * .02;
	MoveSpeed.Y -= MoveSpeed.Y * .02;

	UScreenUtil::UpdateActorLocationWhenOffScreen(this, 20.0f);
}

void AAsteroidsPawn::RegenerateShields(float DeltaSeconds)
{
	if (playerCurrentShields < playerMaxShields)
	{
		playerCurrentShields += shieldRegenRate * DeltaSeconds;
		if (playerCurrentShields > 100.0f)
		{
			playerCurrentShields = 100.0f;
		}
		FMessage message;
		message.floatMessage = playerCurrentShields / playerMaxShields;
		message.typeMessage = EMessageTypes::Float;
		messanger->ShieldsUpdated(message);
	}
}

void AAsteroidsPawn::FireShot()
{
	// If it's ok to fire again
	if (currentBullets < 2)
	{
		const FVector FireDirection = GetActorForwardVector();
		const FRotator FireRotation = FireDirection.Rotation();
		// Spawn projectile at an offset from this pawn
		const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile
			AAsteroidsProjectile* bullet = World->SpawnActor<AAsteroidsProjectile>(SpawnLocation, FireRotation);
		}

		bCanFire = false;

		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AAsteroidsPawn::ShotTimerExpired, FireRate);

		// try and play the sound if specified
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		bCanFire = false;
		currentBullets++;
	}
}

void AAsteroidsPawn::ShotTimerExpired()
{
	bCanFire = true;
}

void AAsteroidsPawn::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FName pro = OtherComp->GetCollisionProfileName();
	if (OtherComp->GetCollisionProfileName() == FName("Asteroid"))
	{
		DealDamage(10);
		damageTimerActive = true;
	}
}

void AAsteroidsPawn::HandleHealthPackPickedUp(FMessage message)
{
	playerCurrentHealth += message.floatMessage;

	if (playerCurrentHealth > 100)
	{
		playerCurrentHealth = 100;
	}

	FMessage newHealthMessage = FMessage();
	newHealthMessage.floatMessage = playerCurrentHealth / playerMaxHealth;
	messanger->UpdatePlayerHealth(newHealthMessage);

	if (playerCurrentHealth >= 50.0f)
	{
		SmokeComponent->DeactivateSystem();
	}

	if (playerCurrentHealth >= 25.0f)
	{
		SmokeComponent->ActivateSystem();
		FireComponent->DeactivateSystem();
	}
}

