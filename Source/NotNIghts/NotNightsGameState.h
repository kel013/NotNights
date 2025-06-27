// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NotNightsGameState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int, Score);

UCLASS()
class NOTNIGHTS_API ANotNightsGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int PlayerScore{ 0 };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int EssentialsCollected{ 0 };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int EssentialsNeeded{ 20 };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool LapComplete{ false };

public:
	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnScoreChanged OnScoreChanged;

	void IncrementScore(int Inc) { PlayerScore += Inc; OnScoreChanged.Broadcast(PlayerScore); };
	void IncrementEssentials(int Inc) { EssentialsCollected += Inc; };
	void ToggleLapComplete(bool Complete) { LapComplete = Complete; };

	UFUNCTION(BlueprintCallable)
	int GetEssentialScore() { return EssentialsCollected; };
	UFUNCTION(BlueprintCallable)
	int GetScore() { return PlayerScore; };
	UFUNCTION(BlueprintCallable)
	bool IsLapComplete() { return LapComplete; };
};
