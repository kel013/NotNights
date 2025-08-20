// Fill out your copyright notice in the Description page of Project Settings.


#include "Ring.h"

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
	if (BoxComponent)
	{
		BoxComponent->SetBoxExtent(FVector(BoxThickness, Radius, Radius));
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

void ARing::OnDirectCollect_Implementation()
{
	ANotNightsGameState* const GameState = GetWorld() != NULL ? GetWorld()->GetGameState<ANotNightsGameState>() : NULL;
	//Check the scores provided by the collectible
	if (Score != 0)
	{
		GameState->IncrementScore(Score);
	}
	if (EssentialScore != 0)
	{
		GameState->IncrementEssentials(EssentialScore);
	}
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
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

		RingStaticMeshComponent->RegisterComponent();
		RingStaticMeshComponent->SetStaticMesh(RingMesh);
		RingStaticMeshComponent->AttachToComponent(BoxComponent, FAttachmentTransformRules::KeepRelativeTransform);
		RingStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		RingStaticMeshComponent->SetRelativeScale3D(FVector(MeshScale, MeshScale, MeshScale));
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

void ARing::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ANotNIghtsCharacter::StaticClass()))
	{
		OnDirectCollect();
	}
}

// Called every frame
void ARing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

