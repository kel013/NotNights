// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelObjectPoolWorldSubsystem.h"

#include "NotNightsWorldSettings.h"

void ULevelObjectPoolWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	ANotNightsWorldSettings* WorldSetting = Cast<ANotNightsWorldSettings>(GetWorld()->GetWorldSettings());
	if (WorldSetting)
	{
		LapActors.Reserve(WorldSetting->Paths.Num());
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

}
void ULevelObjectPoolWorldSubsystem::DisableLap(int LapNum)
{

}