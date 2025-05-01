// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCollectible.h"

// Sets default values
ABasicCollectible::ABasicCollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasicCollectible::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicCollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

