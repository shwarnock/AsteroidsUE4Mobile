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

void UMessanger::PlayerDied()
{
	OnPlayerDied.Broadcast();
}

void UMessanger::FireShot()
{
	OnFireButtonPressed.Broadcast();
}

void UMessanger::BulletDestroyed(FMessage message)
{
	OnBulletDestroyed.Broadcast(message);
}