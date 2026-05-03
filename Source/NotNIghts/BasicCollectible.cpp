// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCollectible.h"

#include "NotNightsGameMode.h"

// Sets default values
ABasicCollectible::ABasicCollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereComponent->InitSphereRadius(100.0f);
	RootComponent = SphereComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SphereComponent);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasicCollectible::OnOverlap);
}

// Called when the game starts or when spawned
void ABasicCollectible::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasicCollectible::OnDirectCollect_Implementation()
{
	ANotNIghtsGameMode* const GameMode = GetWorld() != NULL ? GetWorld()->GetAuthGameMode<ANotNIghtsGameMode>() : NULL;
	if (Score != 0)
	{
		GameMode->IncrementScore(Score);
	}
	if (EssentialScore != 0)
	{
		GameMode->IncrementEssentials(EssentialScore);
	}
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ABasicCollectible::OnLoop_Implementation()
{
	ANotNIghtsGameMode* const GameMode = GetWorld() != NULL ? GetWorld()->GetAuthGameMode<ANotNIghtsGameMode>() : NULL;
	if (Score != 0)
	{
		GameMode->IncrementScore(Score);
	}
	if (EssentialScore != 0)
	{
		GameMode->IncrementEssentials(EssentialScore);
	}
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

// Called every frame
void ABasicCollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

