// Fill out your copyright notice in the Description page of Project Settings.


#include "LapParent.h"

#include "LevelObjectPoolWorldSubsystem.h"
// Sets default values
ALapParent::ALapParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALapParent::BeginPlay()
{
	Super::BeginPlay();
	ULevelObjectPoolWorldSubsystem* LapPool = GetWorld()->GetSubsystem<ULevelObjectPoolWorldSubsystem>();
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	LapPool->RegisterLapActors(AttachedActors, LapNumber);
}

// Called every frame
void ALapParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

