// Fill out your copyright notice in the Description page of Project Settings.


#include "Deposit.h"

#include "NotNightsGameState.h"

// Sets default values
ADeposit::ADeposit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADeposit::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADeposit::DepositEssentials()
{
	ANotNightsGameState* const GameState = GetWorld() != NULL ? GetWorld()->GetGameState<ANotNightsGameState>() : NULL;
	GameState->DepositEssentials();

	if (GameState->IsEssentialsFull())
	{
		GameState->ToggleLapComplete(true);
		GameState->ResetEssentialDeposit();
		SetActorEnableCollision(false);
		SetActorHiddenInGame(true);
		SetActorTickEnabled(false);
	}

}

// Called every frame
void ADeposit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

