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
	Super::BeginPlay();
}

//Game fail state
void ANotNIghtsGameMode::FailPlayer()
{
	UE_LOG(LogTemp, Display, TEXT("Player failed to complete the lap in time"));
}

void ANotNIghtsGameMode::IncrementScore(int Inc)
{
	PlayerScore += Inc;
	OnScoreChanged.Broadcast(PlayerScore);
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
	Result.TotalScore = PlayerScore;
	OnSendLapResults.Broadcast(Result);
	PlayerScore = 0;
	ToggleLapRequirementsComplete(false);
	ResetLapTimer();
}

void ANotNIghtsGameMode::ResetLapTimer()
{
	GetWorldTimerManager().SetTimer(LapTimerHandle, this, &ANotNIghtsGameMode::FailPlayer, LapTimeLimit, false);
};

float ANotNIghtsGameMode::GetLapTimeRemaining()
{
	return GetWorldTimerManager().GetTimerRemaining(LapTimerHandle);
}