// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NotNIghtsGameMode.h"
#include "GameFramework/SaveGame.h"
#include "NotNightsSave.generated.h"

/**
 * 
 */

UCLASS()
class NOTNIGHTS_API UNotNightsSave : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Basic)
	TMap<FString, FLevelResult> MapToScore;

};
