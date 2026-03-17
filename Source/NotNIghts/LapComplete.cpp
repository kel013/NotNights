// Fill out your copyright notice in the Description page of Project Settings.


#include "LapComplete.h"

#include "NotNIghtsGameMode.h"
#include "NotNIghtsCharacter.h"
#include "NotNightsWorldSettings.h"
#include "LevelObjectPoolWorldSubsystem.h"
// Sets default values
ALapComplete::ALapComplete()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LapCompleteCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	LapCompleteCollision->InitBoxExtent(FVector(150.0f, 150.0f, 150.0f));
	RootComponent = LapCompleteCollision;

	LapCompleteCollision->OnComponentBeginOverlap.AddDynamic(this, &ALapComplete::OnOverlapLapComplete);

	CheckpointCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckPointBoxColliderCheckPoint"));
	CheckpointCollision->InitBoxExtent(FVector(10.0f, 200.0f, 500.0f));
	CheckpointCollision->SetupAttachment(LapCompleteCollision);

	CheckpointCollision->OnComponentBeginOverlap.AddDynamic(this, &ALapComplete::OnOverlapLapCheckpoint);
}

// Called when the game starts or when spawned
void ALapComplete::BeginPlay()
{
	Super::BeginPlay();
	
	CheckpointCollision->AttachToComponent(LapCompleteCollision, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called every frame
void ALapComplete::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALapComplete::OnOverlapLapComplete(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ANotNIghtsCharacter::StaticClass()))
	{
		ANotNIghtsGameMode* const GameMode = GetWorld() != NULL ? GetWorld()->GetAuthGameMode<ANotNIghtsGameMode>() : NULL;
		if (GameMode->IsLapComplete())
		{
			ANotNIghtsCharacter* Player = Cast<ANotNIghtsCharacter>(OtherActor);
			ULevelObjectPoolWorldSubsystem* LapPool = GetWorld()->GetSubsystem<ULevelObjectPoolWorldSubsystem>();
			LapPool->DisableLap(Player->GetCurrentLap());
			ANotNightsWorldSettings* WorldSetting = Cast<ANotNightsWorldSettings>(GetWorld()->GetWorldSettings());
			if (Player->GetCurrentLap() + 1 < WorldSetting->GetPathCount())
			{
				Player->IncrementLap();
				GameMode->FinishLap();
				SetActorEnableCollision(false);
				SetActorHiddenInGame(true);
				SetActorTickEnabled(false);
				UE_LOG(LogTemplateCharacter, Display, TEXT("Lap '%i'"), Player->GetCurrentLap());
			}
			else
			{
				GameMode->CompleteLevel();
			}
		}
	}
}

void ALapComplete::OnOverlapLapCheckpoint(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ANotNIghtsCharacter::StaticClass()))
	{
		ULevelObjectPoolWorldSubsystem* LapPool = GetWorld()->GetSubsystem<ULevelObjectPoolWorldSubsystem>();
		LapPool->EnableLap(Cast<ANotNIghtsCharacter>(OtherActor)->GetCurrentLap());
	}
}