// Copyright Epic Games, Inc. All Rights Reserved.

#include "NotNIghtsGameMode.h"
#include "NotNightsGameState.h"
#include "NotNIghtsCharacter.h"
#include "NotNightsWorldSettings.h"
#include "UObject/ConstructorHelpers.h"

ANotNIghtsGameMode::ANotNIghtsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	GameStateClass = ANotNightsGameState::StaticClass();
}

void ANotNIghtsGameMode::BeginPlay()
{
	ANotNightsWorldSettings* WorldSetting = Cast<ANotNightsWorldSettings>(GetWorld()->GetWorldSettings());
	LapTimeLimit = WorldSetting->GetTimeLimit();
	GetWorldTimerManager().SetTimer(LapTimerHandle, this, &ANotNIghtsGameMode::FailPlayer, LapTimeLimit, false);
	TotalLapCount = WorldSetting->GetPathCount();
	CurrentPath = WorldSetting->GetPath(CurrentLap);
	PlayerLapScores.Reserve(TotalLapCount);
	Super::BeginPlay();
}

//Game fail state
void ANotNIghtsGameMode::FailPlayer()
{
	EndLevel(false);
}

void ANotNIghtsGameMode::IncrementScore(int Inc)
{
	GetWorldTimerManager().SetTimer(LinkTimerHandle, this, &ANotNIghtsGameMode::ResetLinkScore, LinkTimeWindow, false);
	LinkScore += Inc;
	CurrentPlayerLapScore += LinkScore;
	OnScoreChanged.Broadcast(CurrentPlayerLapScore);
};

void ANotNIghtsGameMode::DepositEssentials()
{
	EssentialsDeposited += EssentialsCollected; EssentialsCollected = 0;
	OnEssentialChanged.Broadcast(EssentialsCollected);
};

void ANotNIghtsGameMode::IncrementEssentials(int Inc)
{
	EssentialsCollected += Inc;
	OnEssentialChanged.Broadcast(EssentialsCollected);
};

void ANotNIghtsGameMode::FinishLap()
{
	FLapResult Result;
	Result.TotalScore = CurrentPlayerLapScore;

	LevelAScoreMinimum += CurrentPath->GetAMinimum();
	LevelBScoreMinimum += CurrentPath->GetBMinimum();
	LevelCScoreMinimum += CurrentPath->GetCMinimum();

	if (CurrentPlayerLapScore >= CurrentPath->GetAMinimum())
	{
		Result.LapGrade = EGrade::EGrade_A;
	}
	else if (CurrentPlayerLapScore >= CurrentPath->GetBMinimum())
	{
		Result.LapGrade = EGrade::EGrade_B;
	}
	else if (CurrentPlayerLapScore >= CurrentPath->GetCMinimum())
	{
		Result.LapGrade = EGrade::EGrade_C;
	}
	else
	{
		Result.LapGrade = EGrade::EGrade_D;
	}

	OnSendLapResults.Broadcast(Result);
	PlayerTotalScore += CurrentPlayerLapScore;
	PlayerLapScores.Add(CurrentPlayerLapScore);
	CurrentPlayerLapScore = 0;
	ToggleLapRequirementsComplete(false);
	CurrentLap++;

	ANotNightsWorldSettings* WorldSetting = Cast<ANotNightsWorldSettings>(GetWorld()->GetWorldSettings());
	CurrentPath = WorldSetting->GetPath(CurrentLap);

	ResetLapTimer();
}

void ANotNIghtsGameMode::ResetLapTimer()
{
	GetWorldTimerManager().SetTimer(LapTimerHandle, this, &ANotNIghtsGameMode::FailPlayer, LapTimeLimit, false);
};

void ANotNIghtsGameMode::EndLevel(bool Success)
{
	FLevelResult Result;
	PlayerTotalScore += CurrentPlayerLapScore;
	Result.TotalScore = PlayerTotalScore;
	Result.Success = Success;

	if (CurrentPlayerLapScore >= LevelAScoreMinimum)
	{
		Result.LevelGrade = EGrade::EGrade_A;
	}
	else if (CurrentPlayerLapScore >= LevelBScoreMinimum)
	{
		Result.LevelGrade = EGrade::EGrade_B;
	}
	else if (CurrentPlayerLapScore >= LevelCScoreMinimum)
	{
		Result.LevelGrade = EGrade::EGrade_C;
	}
	else
	{
		Result.LevelGrade = EGrade::EGrade_D;
	}

	OnSendLevelResults.Broadcast(Result);
	GetWorldTimerManager().ClearTimer(LapTimerHandle);
}

float ANotNIghtsGameMode::GetLapTimeRemaining()
{
	return GetWorldTimerManager().GetTimerRemaining(LapTimerHandle);
}