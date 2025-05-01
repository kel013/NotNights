// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCollectible.h"

#include "NotNIghtsCharacter.h"

// Sets default values
ABasicCollectible::ABasicCollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BoxCollider"));
	SphereComponent->InitSphereRadius(100.0f);
	RootComponent = SphereComponent;

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasicCollectible::OnOverlap);
}

// Called when the game starts or when spawned
void ABasicCollectible::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ABasicCollectible::OnDirectCollect()
{
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	return true;
}

void ABasicCollectible::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ANotNIghtsCharacter::StaticClass()))
	{
		OnDirectCollect();
	}
}

// Called every frame
void ABasicCollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

