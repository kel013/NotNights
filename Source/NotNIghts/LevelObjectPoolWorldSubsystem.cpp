// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelObjectPoolWorldSubsystem.h"

#include "NotNightsWorldSettings.h"
#include "NotNightsWorldSettings.h"

void ULevelObjectPoolWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	ANotNightsWorldSettings* WorldSetting = Cast<ANotNightsWorldSettings>(GetWorld()->GetWorldSettings());
	if (WorldSetting)
	{
		LapActors.Reserve(WorldSetting->Paths.Num());
	}
}

void ULevelObjectPoolWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
	ANotNightsWorldSettings* WorldSetting = Cast<ANotNightsWorldSettings>(GetWorld()->GetWorldSettings());
	TArray<TSoftObjectPtr<AActor>> Laps = WorldSetting->GetLapParents();
	for (int x = 0; x < Laps.Num(); x++)
	{
		TArray<AActor*> AttachedActors;
		Laps[x]->GetAttachedActors(AttachedActors);
		RegisterLapActors(AttachedActors, x);
		DisableLap(x);
	}
}

void ULevelObjectPoolWorldSubsystem::RegisterLapActor(AActor* Actor, int LapNum)
{
	check(LapNum < LapActors.Num());
	LapActors[LapNum].Add(Actor);
}
void ULevelObjectPoolWorldSubsystem::RegisterLapActors(TArray<AActor*> Actors, int LapNum)
{
	check(LapNum < LapActors.Num());
	LapActors[LapNum].Append(Actors);
}

void ULevelObjectPoolWorldSubsystem::EnableLap(int LapNum)
{
	for (AActor* Actor : LapActors[LapNum])
	{
		Actor->SetActorEnableCollision(true);
		Actor->SetActorHiddenInGame(false);
		Actor->SetActorTickEnabled(true);
	}
}
void ULevelObjectPoolWorldSubsystem::DisableLap(int LapNum)
{
	for (AActor* Actor : LapActors[LapNum])
	{
		Actor->SetActorEnableCollision(false);
		Actor->SetActorHiddenInGame(true);
		Actor->SetActorTickEnabled(false);
	}
}