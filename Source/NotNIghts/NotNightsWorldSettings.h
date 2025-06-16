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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paths", meta = (AllowPrivateAccess = "true"))
	TArray<TSoftObjectPtr<APathSpline>> Paths;

	TSoftObjectPtr<APathSpline> GetPath(int Lap);
};
