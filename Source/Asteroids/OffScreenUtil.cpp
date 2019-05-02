// Fill out your copyright notice in the Description page of Project Settings.


#include "OffScreenUtil.h"


FVector2D UOffScreenUtil::ScreenSize = FVector2D(0, 0);
float UOffScreenUtil::ScreenBuffer = 20.0f;

void UOffScreenUtil::SetScreenSize()
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

bool UOffScreenUtil::CheckForOffScreen(AActor* actor)
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

void UOffScreenUtil::UpdateActorLocationWhenOffScreen(AActor* actor)
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

	if (ScreenLocation.X > ScreenSize.X + ScreenBuffer)
	{
		playerController->DeprojectScreenPositionToWorld(-ScreenBuffer, ScreenLocation.Y, newLocation, dir);
		newLocation.Z = 0;
		actor->SetActorLocation(newLocation);
	}
	else if (ScreenLocation.X < -ScreenBuffer)
	{
		playerController->DeprojectScreenPositionToWorld(ScreenSize.X + ScreenBuffer, ScreenLocation.Y, newLocation, dir);
		newLocation.Z = 0;
		actor->SetActorLocation(newLocation);
	}
	else if (ScreenLocation.Y > ScreenSize.Y + ScreenBuffer)
	{
		playerController->DeprojectScreenPositionToWorld(ScreenLocation.X, -ScreenBuffer, newLocation, dir);
		newLocation.Z = 0;
		actor->SetActorLocation(newLocation);
	}
	else if (ScreenLocation.Y < -ScreenBuffer)
	{
		playerController->DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenSize.Y + ScreenBuffer, newLocation, dir);
		newLocation.Z = 0;
		actor->SetActorLocation(newLocation);
	}
}
