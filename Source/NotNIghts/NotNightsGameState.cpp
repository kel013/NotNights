// Fill out your copyright notice in the Description page of Project Settings.


#include "NotNightsGameState.h"
#include "NotNightsWorldSettings.h"

void ANotNightsGameState::BeginPlay()
{
	ANotNightsWorldSettings* WorldSetting = Cast<ANotNightsWorldSettings>(GetWorld()->GetWorldSettings());
	LapTimeLimit = WorldSetting->GetTimeLimit();
	GetWorldTimerManager().SetTimer(LapTimerHandle, this, &ANotNightsGameState::FailPlayer, LapTimeLimit, false);
	Super::BeginPlay();
}

//Game fail state
void ANotNightsGameState::FailPlayer()
{
	UE_LOG(LogTemp, Display, TEXT("Player failed to complete the lap in time"));
}

void ANotNightsGameState::IncrementScore(int Inc) 
{ 
	PlayerScore += Inc; 
	OnScoreChanged.Broadcast(PlayerScore); 
};

void ANotNightsGameState::DepositEssentials() 
{ 
	EssentialsDeposited += EssentialsCollected; EssentialsCollected = 0; 
	OnEssentialChanged.Broadcast(EssentialsCollected); 
};

void ANotNightsGameState::IncrementEssentials(int Inc) 
{ 
	EssentialsCollected += Inc; 
	OnEssentialChanged.Broadcast(EssentialsCollected); 
};

void ANotNightsGameState::ResetLapTimer()
{
	GetWorldTimerManager().SetTimer(LapTimerHandle, this, &ANotNightsGameState::FailPlayer, LapTimeLimit, false);
};

float ANotNightsGameState::GetLapTimeRemaining()
{
	return GetWorldTimerManager().GetTimerRemaining(LapTimerHandle);
}