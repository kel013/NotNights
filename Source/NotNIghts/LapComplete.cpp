// Fill out your copyright notice in the Description page of Project Settings.


#include "LapComplete.h"

#include "NotNightsGameState.h"
#include "NotNIghtsCharacter.h"
#include "LevelObjectPoolWorldSubsystem.h"
// Sets default values
ALapComplete::ALapComplete()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxComponent->InitBoxExtent(FVector(150.0f, 150.0f, 150.0f));
	SetRootComponent(BoxComponent);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ALapComplete::OnOverlap);
}

// Called when the game starts or when spawned
void ALapComplete::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALapComplete::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALapComplete::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ANotNIghtsCharacter::StaticClass()))
	{
		ANotNightsGameState* const GameState = GetWorld() != NULL ? GetWorld()->GetGameState<ANotNightsGameState>() : NULL;
		if (GameState->IsLapComplete())
		{
			ANotNIghtsCharacter* Player = Cast<ANotNIghtsCharacter>(OtherActor);
			ULevelObjectPoolWorldSubsystem* LapPool = GetWorld()->GetSubsystem<ULevelObjectPoolWorldSubsystem>();
			LapPool->DisableLap(Player->GetCurrentLap());
			Player->IncrementLap();
			GameState->ToggleLapComplete(false);
		}
	}
}