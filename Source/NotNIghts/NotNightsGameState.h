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
	int EssentialsNeeded{ 1 };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool LapComplete{ false };

	int EssentialsDeposited{ 0 };

public:
	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnScoreChanged OnScoreChanged;

	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnScoreChanged OnEssentialChanged;

	void IncrementScore(int Inc);
	void DepositEssentials();
	void IncrementEssentials(int Inc);
	void ToggleLapComplete(bool Complete) { LapComplete = Complete; };

	void ResetEssentialDeposit() { EssentialsDeposited = 0; };

	bool IsEssentialsFull() { return EssentialsDeposited >= EssentialsNeeded; };

	UFUNCTION(BlueprintCallable)
	int GetEssentialScore() { return EssentialsCollected; };
	UFUNCTION(BlueprintCallable)
	int GetEssentialsDeposited() { return EssentialsDeposited; };
	UFUNCTION(BlueprintCallable)
	int GetScore() { return PlayerScore; };
	UFUNCTION(BlueprintCallable)
	bool IsLapComplete() { return LapComplete; };
};
