// Fill out your copyright notice in the Description page of Project Settings.


#include "NotNightsWorldSettings.h"

TSoftObjectPtr<APathSpline> ANotNightsWorldSettings::GetPath(int Lap)
{
	return Paths[Lap];
}