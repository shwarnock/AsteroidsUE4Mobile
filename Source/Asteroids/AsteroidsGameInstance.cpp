// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidsGameInstance.h"

UAsteroidsGameInstance::UAsteroidsGameInstance()
{
	messanger = NewObject<UMessanger>();
}

UMessanger* UAsteroidsGameInstance::GetMessanger()
{
	return messanger;
}
