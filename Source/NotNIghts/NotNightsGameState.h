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

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int PlayerScore{ 0 };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int EssentialsCollected{ 0 };

public:
	//ANotNightsGameState();

	void IncrementScore(int Inc) { PlayerScore += Inc; };
	void IncrementEssentials(int Inc) { EssentialsCollected += Inc; };

	UFUNCTION(BlueprintCallable)
	int GetEssentialScore() { return EssentialsCollected; };
	UFUNCTION(BlueprintCallable)
	int GetScore() { return PlayerScore; };
};
