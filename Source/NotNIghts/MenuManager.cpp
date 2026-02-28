// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuManager.h"
#include <Kismet/GameplayStatics.h>

void AMenuManager::OnEnterMenu_Implementation()
{
	EnterMenu();
}

void AMenuManager::EnterMenu()
{
	if (AActor* CameraActor = Cast<AActor>(MenuCamera))
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(CameraActor, 1.0);
	}

	IsActive = true;
}