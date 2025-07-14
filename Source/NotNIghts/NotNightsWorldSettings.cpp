// Fill out your copyright notice in the Description page of Project Settings.


#include "NotNightsWorldSettings.h"

TSoftObjectPtr<APathSpline> ANotNightsWorldSettings::GetPath(int Lap)
{
	check(Lap < Paths.Num());
	return Paths[Lap];
}

int ANotNightsWorldSettings::GetPathCount()
{
	return Paths.Num();
}

TArray<TSoftObjectPtr<AActor>> ANotNightsWorldSettings::GetLapParents()
{
	return LapParents;
}