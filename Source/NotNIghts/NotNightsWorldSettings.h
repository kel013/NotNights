// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "PathSpline.h"
#include "NotNightsWorldSettings.generated.h"

/**
 * 
 */
UCLASS()
class NOTNIGHTS_API ANotNightsWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laps", meta = (AllowPrivateAccess = "true"))
	TArray<TSoftObjectPtr<APathSpline>> Paths;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laps", meta = (AllowPrivateAccess = "true"))
	TArray<TSoftObjectPtr<AActor>> LapParents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laps", meta = (AllowPrivateAccess = "true"))
	bool HideOtherLapObjects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laps", meta = (AllowPrivateAccess = "true"))
	float LapTimeLimit = 120.0f;

	TSoftObjectPtr<APathSpline> GetPath(int Lap);
	int GetPathCount();

	TArray<TSoftObjectPtr<AActor>> GetLapParents();
	bool GetHideOtherLaps();
	float GetTimeLimit();
};
