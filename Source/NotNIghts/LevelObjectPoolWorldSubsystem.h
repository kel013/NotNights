// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LevelObjectPoolWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class NOTNIGHTS_API ULevelObjectPoolWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void RegisterLapActor(AActor* Actor, int LapNum);
	void RegisterLapActors(TArray<AActor*> Actors);

	void EnableLap(int LapNum);
	void DisableLap(int LapNum);
private:
	TArray<TArray<AActor*>> LapActors;
};
