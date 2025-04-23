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

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxComponent->InitBoxExtent(FVector(20.0f, 500.0f, 500.0f));
	RootComponent = BoxComponent;
}

void ARing::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (BoxComponent)
	{
		BoxComponent->SetBoxExtent(FVector(20.0f, Radius, Radius));
	}
	for (UStaticMeshComponent* MeshComponent : RingStaticMesh)
	{
		if (MeshComponent)
		{
			MeshComponent->DestroyComponent();
		}
	}
	RingStaticMesh.Empty();
	SetUpRingObjects();
}

void ARing::SetUpRingObjects()
{
	double Degree = 360.0f / NumberOfSections;
	for (int x = 0; x < NumberOfSections; x++)
	{
		FString MeshString = "RingBall";
		MeshString.Append(FString::FromInt(x));
		FName MeshName = FName(*MeshString);
		UStaticMeshComponent* RingStaticMeshComponent;

		RingStaticMeshComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), MeshName);

		RingStaticMeshComponent->SetupAttachment(RootComponent);
		RingStaticMeshComponent->SetStaticMesh(RingMesh);
		RingStaticMeshComponent->RegisterComponent();

		FVector Location = FVector::UpVector * Radius;
		Location = Location.RotateAngleAxis(Degree * x, FVector::ForwardVector);

		RingStaticMeshComponent->SetWorldLocation(Location);
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

