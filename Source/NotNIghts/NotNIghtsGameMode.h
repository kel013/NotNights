// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NotNIghtsGameMode.generated.h"

USTRUCT(BlueprintType)
struct FLapResult
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int TotalScore;


};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int, Score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSendLapResults, FLapResult, Result);
UCLASS(minimalapi)
class ANotNIghtsGameMode : public AGameModeBase
{
	GENERATED_BODY()



public:
	ANotNIghtsGameMode();

protected:
	virtual void BeginPlay() override;

	void FailPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int PlayerScore{ 0 };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int EssentialsCollected{ 0 };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int EssentialsNeeded{ 1 };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool LapComplete{ false };

	int EssentialsDeposited{ 0 };

	FTimerHandle LapTimerHandle;
	float LapTimeLimit;

public:
	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnScoreChanged OnScoreChanged;

	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnScoreChanged OnEssentialChanged;
	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnSendLapResults OnSendLapResults;

	void IncrementScore(int Inc);
	void DepositEssentials();
	void IncrementEssentials(int Inc);
	void FinishLap();
	void ToggleLapRequirementsComplete(bool Complete) { LapComplete = Complete; };
	void ResetLapTimer();

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
	UFUNCTION(BlueprintCallable)
	float GetLapTimeRemaining();
};



