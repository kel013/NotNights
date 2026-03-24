// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableBase.h"

#include "NotNIghtsCharacter.h"

// Sets default values
ACollectableBase::ACollectableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACollectableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACollectableBase::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ANotNIghtsCharacter::StaticClass()))
	{
		Execute_OnDirectCollect(this);
	}
}

// Called every frame
void ACollectableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

