// Fill out your copyright notice in the Description page of Project Settings.


#include "Deposit.h"

#include "NotNightsGameState.h"
#include "NotNIghtsCharacter.h"

// Sets default values
ADeposit::ADeposit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxComponent->InitBoxExtent(FVector(500.0f, 500.0f, 500.0f));
	SetRootComponent(BoxComponent);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADeposit::OnOverlap);
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

void ADeposit::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ANotNIghtsCharacter::StaticClass()))
	{
		DepositEssentials();
	}
}

// Called every frame
void ADeposit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

