// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NotNightsGameState.generated.h"

/**
 * 
 */
UCLASS()
class NOTNIGHTS_API ANotNightsGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	//ANotNightsGameState();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int PlayerScore{ 0 };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int EssentialsCollected{ 0 };
};
