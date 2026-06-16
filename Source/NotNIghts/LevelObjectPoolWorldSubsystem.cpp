// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelObjectPoolWorldSubsystem.h"
#include "Deposit.h"
#include "NotNightsWorldSettings.h"
#include "Collectible.h"

void ULevelObjectPoolWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void ULevelObjectPoolWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::PostInitialize();
	ANotNightsWorldSettings* WorldSetting = Cast<ANotNightsWorldSettings>(GetWorld()->GetWorldSettings());
	TArray<TSoftObjectPtr<AActor>> Laps = WorldSetting->GetLapParents();
	LapActors.Reserve(WorldSetting->Paths.Num());
	for (int x = 0; x < Laps.Num(); x++)
	{
		TArray<AActor*> AttachedActors;
		Laps[x]->GetAttachedActors(AttachedActors);
		RegisterLapActors(AttachedActors,WorldSetting->GetHideOtherLaps());
	}
	if (Laps.IsEmpty() && WorldSetting->GetHideOtherLaps())
	{
		EnableLap(0);
	}
}

void ULevelObjectPoolWorldSubsystem::RegisterLapActor(AActor* Actor, int LapNum)
{
	check(LapNum < LapActors.Num());
	LapActors[LapNum].Add(Actor);
}
void ULevelObjectPoolWorldSubsystem::RegisterLapActors(TArray<AActor*> Actors,bool HideLaps)
{
	LapActors.Add(Actors);
	if (!HideLaps)
	{
		return;
	}
	for (AActor* Actor : Actors)
	{
		Actor->SetActorEnableCollision(false);
		Actor->SetActorHiddenInGame(true);
		Actor->SetActorTickEnabled(false);
	}
}

void ULevelObjectPoolWorldSubsystem::EnableLap(int LapNum)
{
	for (AActor* Actor : LapActors[LapNum])
	{
		if (Actor->IsA(ADeposit::StaticClass()))
		{
			continue;
		}
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