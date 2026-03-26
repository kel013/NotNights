// Fill out your copyright notice in the Description page of Project Settings.


#include "Ring.h"

#include "NotNightsGameMode.h"
#include "NotNIghtsCharacter.h"

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
	BoxComponent->InitBoxExtent(FVector(BoxThickness, 500.0f, 500.0f));
	SetRootComponent(BoxComponent);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ARing::OnOverlap);
}

void ARing::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
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

void ARing::OnDirectCollect_Implementation()
{
	ANotNIghtsGameMode* const GameMode = GetWorld() != NULL ? GetWorld()->GetAuthGameMode<ANotNIghtsGameMode>() : NULL;
	//Check the scores provided by the collectible
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
	SetRingMeshPositions();
}

void ARing::SetRingMeshPositions()
{
	check(RingStaticMesh.Num() == NumberOfSections);
	double Degree = 360.0f / NumberOfSections;
	for(int x = 0; x < NumberOfSections; x++)
	{
		UStaticMeshComponent* RingStaticMeshComponent = RingStaticMesh[x];

		RingStaticMeshComponent->SetRelativeScale3D(FVector(MeshScale, MeshScale, MeshScale));
		FVector Location = FVector::UpVector * Radius;
		Location = Location.RotateAngleAxis(Degree * x, FVector::ForwardVector);
		RingStaticMeshComponent->SetRelativeLocation(Location);
	}
}

void ARing::SetCollisionBoxExtents()
{
	if (BoxComponent)
	{
		BoxComponent->SetBoxExtent(FVector(BoxThickness, Radius, Radius));
	}
}

void ARing::SetUpRingObjects()
{
	SetCollisionBoxExtents();
	for (int x = 0; x < NumberOfSections; x++)
	{
		FString MeshString = "RingBall";
		MeshString.Append(FString::FromInt(x));
		FName MeshName = FName(*MeshString);
		UStaticMeshComponent* RingStaticMeshComponent;

		RingStaticMeshComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), MeshName);

		RingStaticMeshComponent->RegisterComponent();
		RingStaticMeshComponent->SetStaticMesh(RingMesh);
		RingStaticMeshComponent->AttachToComponent(BoxComponent, FAttachmentTransformRules::KeepRelativeTransform);
		RingStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		RingStaticMesh.Emplace(RingStaticMeshComponent);
	}
	SetRingMeshPositions();
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

