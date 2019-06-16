// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenUtil.h"


FVector2D UScreenUtil::ScreenSize = FVector2D(0, 0);
APlayerController* UScreenUtil::PlayerController = nullptr;

void UScreenUtil::SetScreenSize()
{
	FVector2D Result = FVector2D(0, 0);
	FVector newLocation = FVector::ZeroVector;

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize( /*out*/Result);
	}

	ScreenSize.X = Result.X;
	ScreenSize.Y = Result.Y;
}

FVector2D UScreenUtil::GetScreenSize()
{
	if (ScreenSize.X == 0)
	{
		SetScreenSize();
	}

	return ScreenSize;
}

FVector UScreenUtil::GetWorldPosFromScreenPos(FVector2D ScreenPos, AActor* actor)
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(actor->GetWorld(), 0);
	FVector dir = FVector::ZeroVector;
	FVector NewLocation;
	playerController->DeprojectScreenPositionToWorld(ScreenPos.X, ScreenPos.Y, NewLocation, dir);
	NewLocation.Z = 0;
	return NewLocation;
}

bool UScreenUtil::CheckForOffScreen(AActor* actor)
{
	FVector2D ScreenLocation = FVector2D::ZeroVector;
	APlayerController* playerController = UGameplayStatics::GetPlayerController(actor->GetWorld(), 0);
	FVector actorLocation = actor->GetActorLocation();
	playerController->ProjectWorldLocationToScreen(actorLocation, ScreenLocation);;

	if (ScreenSize.X == 0 || ScreenSize.Y == 0)
	{
		SetScreenSize();
	}

	if (ScreenSize.X < ScreenLocation.X || ScreenSize.Y < ScreenLocation.Y || 0 > ScreenLocation.X || 0 > ScreenLocation.Y)
	{
		return true;
	}

	return false;
}

void UScreenUtil::UpdateActorLocationWhenOffScreen(AActor* actor, float buffer)
{
	FVector2D ScreenLocation = FVector2D::ZeroVector;
	APlayerController* playerController = UGameplayStatics::GetPlayerController(actor->GetWorld(), 0);
	FVector dir = FVector::ZeroVector;
	FVector projectileLocation = actor->GetActorLocation();
	playerController->ProjectWorldLocationToScreen(projectileLocation, ScreenLocation);

	FVector2D Result = FVector2D(0, 0);
	FVector newLocation = FVector::ZeroVector;

	if (ScreenSize.X == 0 || ScreenSize.Y == 0)
	{
		SetScreenSize();
	}

	if (ScreenLocation.X > ScreenSize.X + buffer)
	{
		ScreenLocation.X = -buffer;
		newLocation = GetWorldPosFromScreenPos(ScreenLocation, actor);
		actor->SetActorLocation(newLocation);
	}
	else if (ScreenLocation.X < -buffer)
	{
		ScreenLocation.X = ScreenSize.X + buffer;
		newLocation = GetWorldPosFromScreenPos(ScreenLocation, actor);
		actor->SetActorLocation(newLocation);
	}
	else if (ScreenLocation.Y > ScreenSize.Y + buffer)
	{
		ScreenLocation.Y = -buffer;
		newLocation = GetWorldPosFromScreenPos(ScreenLocation, actor);
		actor->SetActorLocation(newLocation);
	}
	else if (ScreenLocation.Y < -buffer)
	{
		ScreenLocation.Y = ScreenSize.Y + buffer;
		newLocation = GetWorldPosFromScreenPos(ScreenLocation, actor);
		actor->SetActorLocation(newLocation);
	}
}
