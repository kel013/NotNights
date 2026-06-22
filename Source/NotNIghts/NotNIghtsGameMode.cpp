// Copyright Epic Games, Inc. All Rights Reserved.

#include "NotNIghtsGameMode.h"
#include "NotNightsGameState.h"
#include "NotNIghtsCharacter.h"
#include "NotNightsSave.h"
#include "Kismet/GameplayStatics.h"
#include "NotNightsWorldSettings.h"
#include "UObject/ConstructorHelpers.h"

ANotNIghtsGameMode::ANotNIghtsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/EssentialUtility/Player.Player"));
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
	FScoreChange Change;
	Change.Change = LinkScore;
	Change.Score = CurrentPlayerLapScore;
	OnScoreChanged.Broadcast(Change);
};

void ANotNIghtsGameMode::DepositEssentials()
{
	FScoreChange Change;
	Change.Change = -EssentialsCollected;
	EssentialsDeposited += EssentialsCollected; EssentialsCollected = 0;
	Change.Score = EssentialsCollected;
	OnEssentialChanged.Broadcast(Change);
	FEssentialDeposited Deposit;
	Deposit.Deposited = EssentialsDeposited;
	Deposit.Needed = EssentialsNeeded- EssentialsDeposited;
	OnEssentialDeposited.Broadcast(Deposit);
};

void ANotNIghtsGameMode::IncrementEssentials(int Inc)
{
	EssentialsCollected += Inc;
	FScoreChange Change;
	Change.Change = Inc;
	Change.Score = EssentialsCollected;
	OnEssentialChanged.Broadcast(Change);
};

void ANotNIghtsGameMode::SendLapResults()
{
	FLapResult LapResult;
	LapResult.TotalScore = CurrentPlayerLapScore;

	LevelAScoreMinimum += CurrentPath->GetAMinimum();
	LevelBScoreMinimum += CurrentPath->GetBMinimum();
	LevelCScoreMinimum += CurrentPath->GetCMinimum();

	if (CurrentPlayerLapScore >= CurrentPath->GetAMinimum())
	{
		LapResult.LapGrade = EGrade::EGrade_A;
	}
	else if (CurrentPlayerLapScore >= CurrentPath->GetBMinimum())
	{
		LapResult.LapGrade = EGrade::EGrade_B;
	}
	else if (CurrentPlayerLapScore >= CurrentPath->GetCMinimum())
	{
		LapResult.LapGrade = EGrade::EGrade_C;
	}
	else
	{
		LapResult.LapGrade = EGrade::EGrade_D;
	}

	OnSendLapResults.Broadcast(LapResult);
}

void ANotNIghtsGameMode::FinishLap()
{
	SendLapResults();
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
	SendLapResults();

	FLevelResult Result;
	PlayerTotalScore += CurrentPlayerLapScore;
	Result.TotalScore = PlayerTotalScore;
	Result.Success = Success;

	LevelAScoreMinimum += CurrentPath->GetAMinimum();
	LevelBScoreMinimum += CurrentPath->GetBMinimum();
	LevelCScoreMinimum += CurrentPath->GetCMinimum();

	if (PlayerTotalScore >= LevelAScoreMinimum)
	{
		Result.LevelGrade = EGrade::EGrade_A;
	}
	else if (PlayerTotalScore >= LevelBScoreMinimum)
	{
		Result.LevelGrade = EGrade::EGrade_B;
	}
	else if (PlayerTotalScore >= LevelCScoreMinimum)
	{
		Result.LevelGrade = EGrade::EGrade_C;
	}
	else
	{
		Result.LevelGrade = EGrade::EGrade_D;
	}

	OnSendLevelResults.Broadcast(Result);
	GetWorldTimerManager().ClearTimer(LapTimerHandle);

	UNotNightsSave* Save = nullptr;

	FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, LevelName);

	if (UGameplayStatics::DoesSaveGameExist("NotNights", 0))
	{
		Save = Cast<UNotNightsSave>(UGameplayStatics::LoadGameFromSlot("NotNights", 0));
		TMap<FString, FLevelResult>& MapToScore = Save->MapToScore;
		auto it = MapToScore.Find(LevelName);
		if (it != nullptr)
		{
			if (it->TotalScore < Result.TotalScore)
			{
				MapToScore.Add(LevelName, Result);
			}
		}
		else
		{
			MapToScore.Emplace(LevelName, PlayerTotalScore);
		}
		UGameplayStatics::SaveGameToSlot(Save, "NotNights", 0);
	}
	else
	{
		Save = Cast<UNotNightsSave>(UGameplayStatics::CreateSaveGameObject(UNotNightsSave::StaticClass()));
		TMap<FString, FLevelResult>& MapToScore = Save->MapToScore;
		MapToScore.Emplace(LevelName, Result);
		UGameplayStatics::SaveGameToSlot(Save, "NotNights", 0);
	}
}

float ANotNIghtsGameMode::GetLapTimeRemaining()
{
	return GetWorldTimerManager().GetTimerRemaining(LapTimerHandle);
}