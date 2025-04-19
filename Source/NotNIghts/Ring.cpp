// Fill out your copyright notice in the Description page of Project Settings.


#include "Ring.h"

// Sets default values
ARing::ARing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RingMesh)
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
		if (SphereMeshAsset.Succeeded())
		{
			RingMesh = SphereMeshAsset.Object;
		}
	}

	UStaticMeshComponent* CenterRing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Center"));

	CenterRing->SetupAttachment(RootComponent);
	CenterRing->SetStaticMesh(RingMesh);

	double Degree = 360.0f / NumberOfSections;
	for (int x = 0; x < NumberOfSections; x++)
	{
		FString MeshString = "RingBall";
		MeshString.Append(FString::FromInt(x));
		FName MeshName = FName(*MeshString);
		UStaticMeshComponent*  RingStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(MeshName);

		RingStaticMeshComponent->SetupAttachment(CenterRing);
		RingStaticMeshComponent->SetStaticMesh(RingMesh);

		FVector Location = FVector::UpVector * Radius;
		Location = Location.RotateAngleAxis(Degree * x, FVector::ForwardVector);

		RingStaticMeshComponent->SetRelativeLocation(Location);
		RingStaticMesh.Emplace(RingStaticMeshComponent);
	}

}

// Called when the game starts or when spawned
void ARing::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

