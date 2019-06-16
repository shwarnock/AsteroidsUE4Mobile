// Fill out your copyright notice in the Description page of Project Settings.


#include "Messanger.h"

void UMessanger::UpdatePlayerHealth(FMessage message)
{
	OnDamageDealt.Broadcast(message);
}

void UMessanger::AsteroidDestroyed(FMessage message)
{
	OnAsteroidDestroyed.Broadcast(message);
}

void UMessanger::PlayerDied(FMessage message)
{
	OnPlayerDied.Broadcast(message);
}

void UMessanger::FireShot()
{
	OnFireButtonPressed.Broadcast();
}

void UMessanger::BulletDestroyed(FMessage message)
{
	OnBulletDestroyed.Broadcast(message);
}

void UMessanger::UpdatePlayerScore(FMessage message)
{
	OnUpdatePlayerScore.Broadcast(message);
}

void UMessanger::PlayerScoreWasUpdated(FMessage message)
{
	OnPlayerScoreWasUpdated.Broadcast(message);
}

void UMessanger::HealthPackPickedUp(FMessage message)
{
	OnHealthPackPickedUp.Broadcast(message);
}

void UMessanger::UpdateLevel(FMessage message)
{
	OnLevelIsUpdated.Broadcast(message);
}

void UMessanger::ShieldsUpdated(FMessage message)
{
	OnShieldsUpdated.Broadcast(message);
}