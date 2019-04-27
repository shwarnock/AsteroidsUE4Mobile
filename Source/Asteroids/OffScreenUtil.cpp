// Fill out your copyright notice in the Description page of Project Settings.


#include "OffScreenUtil.h"


FVector2D OffScreenUtil::ScreenSize = FVector2D(0, 0);
float OffScreenUtil::ScreenBuffer = 20.0f;

void OffScreenUtil::SetScreenSize()
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

void OffScreenUtil::CheckForOffScreen(AActor* actor)
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
