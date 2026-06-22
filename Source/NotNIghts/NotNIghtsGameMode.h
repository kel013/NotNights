// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PathSpline.h"
#include "GameFramework/GameModeBase.h"
#include "NotNIghtsGameMode.generated.h"

UENUM(BlueprintType)
enum class EGrade : uint8
{
	EGrade_A	UMETA(DisplayName = "A"),
	EGrade_B	UMETA(DisplayName = "B"),
	EGrade_C	UMETA(DisplayName = "C"),
	EGrade_D	UMETA(DisplayName = "D")
};

USTRUCT(BlueprintType)
struct FLapResult
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int TotalScore;

	UPROPERTY(BlueprintReadWrite)
	EGrade LapGrade;
};

USTRUCT(BlueprintType)
struct FLevelResult
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int TotalScore;
	UPROPERTY(BlueprintReadWrite)
	bool Success;

	UPROPERTY(BlueprintReadWrite)
	EGrade LevelGrade;
};

USTRUCT(BlueprintType)
struct FEssentialDeposited
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int Deposited;
	UPROPERTY(BlueprintReadWrite)
	int Needed;

};

USTRUCT(BlueprintType)
struct FScoreChange
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int Score;
	UPROPERTY(BlueprintReadWrite)
	int Change;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, FScoreChange, Score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEssentialDeposited, FEssentialDeposited, Deposited);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSendLapResults, FLapResult, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSendLevelResults, FLevelResult, Result);
UCLASS(minimalapi)
class ANotNIghtsGameMode : public AGameModeBase
{
	GENERATED_BODY()



public:
	ANotNIghtsGameMode();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void FailPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int PlayerTotalScore{ 0 };
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int CurrentPlayerLapScore{ 0 };
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<int> PlayerLapScores;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int EssentialsCollected{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EssentialsNeeded{ 1 };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool LapComplete{ false };

	int EssentialsDeposited{ 0 };

	FTimerHandle LapTimerHandle;
	float LapTimeLimit;

	FTimerHandle LinkTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LinkTimeWindow{1.0f};
	int LinkScore{ 0 };

	int CurrentLap{ 0 };
	
	TSoftObjectPtr <APathSpline> CurrentPath;

	void ResetLinkScore() { LinkScore = 0; };

	//Later calculate the minimum score needed for the grades of the entire level. Basically the minimums for each lap combined is the minimum
	int LevelAScoreMinimum{ 0 };
	int LevelBScoreMinimum{ 0 };
	int LevelCScoreMinimum{ 0 };

public:
	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnScoreChanged OnScoreChanged;

	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnScoreChanged OnEssentialChanged;
	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnEssentialDeposited OnEssentialDeposited;
	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnSendLapResults OnSendLapResults;
	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnSendLevelResults OnSendLevelResults;

	void IncrementScore(int Inc);
	void DepositEssentials();
	void IncrementEssentials(int Inc);
	void SendLapResults();
	void FinishLap();
	int GetCurrentLap() { return CurrentLap; };
	void ToggleLapRequirementsComplete(bool Complete) { LapComplete = Complete; };
	void ResetLapTimer();

	void EndLevel(bool Success);

	void ResetEssentialDeposit() { EssentialsDeposited = 0; };

	bool IsEssentialsFull() { return EssentialsDeposited >= EssentialsNeeded; };

	UFUNCTION(BlueprintCallable)
	int GetEssentialScore() { return EssentialsCollected; };
	UFUNCTION(BlueprintCallable)
	int GetEssentialsDeposited() { return EssentialsDeposited; };
	UFUNCTION(BlueprintCallable)
	int GetLapScore() { return CurrentPlayerLapScore; };
	UFUNCTION(BlueprintCallable)
	bool IsLapComplete() { return LapComplete; };
	UFUNCTION(BlueprintCallable)
	float GetLapTimeRemaining();

	TSoftObjectPtr<APathSpline> GetCurrentPath() { return CurrentPath; };

	int TotalLapCount;
};



