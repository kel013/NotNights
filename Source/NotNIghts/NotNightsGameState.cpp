// Fill out your copyright notice in the Description page of Project Settings.


#include "NotNightsGameState.h"

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