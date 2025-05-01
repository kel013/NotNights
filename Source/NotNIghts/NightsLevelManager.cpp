// Fill out your copyright notice in the Description page of Project Settings.


#include "NightsLevelManager.h"

// Sets default values
ANightsLevelManager::ANightsLevelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANightsLevelManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANightsLevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

APathSpline* ANightsLevelManager::GetPath(int Lap)
{
	return Paths[Lap];

}

