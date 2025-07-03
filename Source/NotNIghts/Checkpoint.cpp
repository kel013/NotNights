// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"

#include "NotNightsGameState.h"

#include "NotNIghtsCharacter.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ANotNIghtsCharacter::StaticClass()))
	{
		ANotNightsGameState* const GameState = GetWorld() != NULL ? GetWorld()->GetGameState<ANotNightsGameState>() : NULL;
		if (GameState->IsLapComplete())
		{
			Cast<ANotNIghtsCharacter>(OtherActor)->IncrementLap();
			GameState->ToggleLapComplete(false);
		}
	}
}