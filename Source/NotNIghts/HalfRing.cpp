// Fill out your copyright notice in the Description page of Project Settings.


#include "HalfRing.h"

void AHalfRing::SetUpRingObjects()
{
	if (BoxComponent)
	{
		BoxComponent->SetBoxExtent(FVector(BoxThickness, Radius, (StraightLength+Radius)/2));
		BoxComponent->SetRelativeLocation(FVector(0, 0, (StraightLength + Radius) / 2));
	}
	float CircleCircumference = Radius * PI;
	float RingLength = 2 * StraightLength + CircleCircumference;
	int CircleNumberOfSections = (CircleCircumference / RingLength) * NumberOfSections;
	if ((NumberOfSections % 2 == 0 && CircleNumberOfSections % 2 == 1) || (NumberOfSections % 2 == 1 && CircleNumberOfSections % 2 == 0))
	{
		CircleNumberOfSections += 1;
	}

	int LengthWiseNumberOfSections = NumberOfSections - CircleNumberOfSections;
	float SpaceBetweenSections = (2* StraightLength) / LengthWiseNumberOfSections;
	for (int x = 0; x < LengthWiseNumberOfSections / 2; x++)
	{
		FString MeshStringLeft = "RingBall";
		MeshStringLeft.Append(FString::FromInt(2 * x));
		FName LeftMeshName = FName(*MeshStringLeft);
		UStaticMeshComponent* LeftRingStaticMeshComponent;

		LeftRingStaticMeshComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), LeftMeshName);

		LeftRingStaticMeshComponent->RegisterComponent();
		LeftRingStaticMeshComponent->SetStaticMesh(RingMesh);
		LeftRingStaticMeshComponent->AttachToComponent(BoxComponent, FAttachmentTransformRules::KeepRelativeTransform);
		LeftRingStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		LeftRingStaticMeshComponent->SetRelativeScale3D(FVector(MeshScale, MeshScale, MeshScale));
		FVector LocationLeft = FVector::LeftVector * Radius;
		LocationLeft += FVector::UpVector * x * SpaceBetweenSections;
		LocationLeft -= FVector(0, 0, (StraightLength + Radius) / 2);
		LeftRingStaticMeshComponent->SetRelativeLocation(LocationLeft);
		RingStaticMesh.Emplace(LeftRingStaticMeshComponent);

		FString MeshStringRight = "RingBall";
		MeshStringRight.Append(FString::FromInt(2 * x + 1));
		FName RightMeshName = FName(*MeshStringRight);
		UStaticMeshComponent* RightRingStaticMeshComponent;

		RightRingStaticMeshComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), RightMeshName);

		RightRingStaticMeshComponent->RegisterComponent();
		RightRingStaticMeshComponent->SetStaticMesh(RingMesh);
		RightRingStaticMeshComponent->AttachToComponent(BoxComponent, FAttachmentTransformRules::KeepRelativeTransform);
		RightRingStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		RightRingStaticMeshComponent->SetRelativeScale3D(FVector(MeshScale, MeshScale, MeshScale));
		FVector LocationRight = FVector::RightVector * Radius;
		LocationRight += FVector::UpVector * x * SpaceBetweenSections;
		LocationRight -= FVector(0, 0, (StraightLength + Radius) / 2);
		RightRingStaticMeshComponent->SetRelativeLocation(LocationRight);
		RingStaticMesh.Emplace(RightRingStaticMeshComponent);
	}

	double Degree = 180.0f / (CircleNumberOfSections-1);
	FVector HalfCircleCenter = FVector::UpVector * (StraightLength - ((StraightLength + Radius) / 2));
	for (int x = 0; x < CircleNumberOfSections; x++)
	{
		FString MeshString = "RingBall";
		MeshString.Append(FString::FromInt(LengthWiseNumberOfSections + x));
		FName MeshName = FName(*MeshString);
		UStaticMeshComponent* RingStaticMeshComponent;

		RingStaticMeshComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), MeshName);

		RingStaticMeshComponent->RegisterComponent();
		RingStaticMeshComponent->SetStaticMesh(RingMesh);
		RingStaticMeshComponent->AttachToComponent(BoxComponent, FAttachmentTransformRules::KeepRelativeTransform);
		RingStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		RingStaticMeshComponent->SetRelativeScale3D(FVector(MeshScale, MeshScale, MeshScale));
		FVector Location = FVector::UpVector * Radius;
		Location = Location.RotateAngleAxis((Degree * x)-90, FVector::ForwardVector);
		Location += HalfCircleCenter;
		RingStaticMeshComponent->SetRelativeLocation(Location);
		RingStaticMesh.Emplace(RingStaticMeshComponent);
	}


}