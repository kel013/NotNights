// Fill out your copyright notice in the Description page of Project Settings.


#include "HalfRing.h"

void AHalfRing::SetRingMeshPositions()
{
	check(RingStaticMesh.Num() == NumberOfSections);

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
		UStaticMeshComponent* LeftRingStaticMeshComponent = RingStaticMesh[2*x];

		LeftRingStaticMeshComponent->SetRelativeScale3D(FVector(MeshScale, MeshScale, MeshScale));
		FVector LocationLeft = FVector::LeftVector * Radius;
		LocationLeft += FVector::UpVector * x * SpaceBetweenSections;
		LocationLeft -= FVector(0, 0, (StraightLength + Radius) / 2);
		LeftRingStaticMeshComponent->SetRelativeLocation(LocationLeft);

		UStaticMeshComponent* RightRingStaticMeshComponent = RingStaticMesh[2 * x + 1];

		RightRingStaticMeshComponent->SetRelativeScale3D(FVector(MeshScale, MeshScale, MeshScale));
		FVector LocationRight = FVector::RightVector * Radius;
		LocationRight += FVector::UpVector * x * SpaceBetweenSections;
		LocationRight -= FVector(0, 0, (StraightLength + Radius) / 2);
		RightRingStaticMeshComponent->SetRelativeLocation(LocationRight);
	}

	double Degree = 180.0f / (CircleNumberOfSections-1);
	FVector HalfCircleCenter = FVector::UpVector * (StraightLength - ((StraightLength + Radius) / 2));
	for (int x = 0; x < CircleNumberOfSections; x++)
	{
		UStaticMeshComponent* RingStaticMeshComponent = RingStaticMesh[LengthWiseNumberOfSections + x];

		RingStaticMeshComponent->SetRelativeScale3D(FVector(MeshScale, MeshScale, MeshScale));
		FVector Location = FVector::UpVector * Radius;
		Location = Location.RotateAngleAxis((Degree * x)-90, FVector::ForwardVector);
		Location += HalfCircleCenter;
		RingStaticMeshComponent->SetRelativeLocation(Location);
	}
}

void AHalfRing::SetCollisionBoxExtents()
{
	if (BoxComponent)
	{
		BoxComponent->SetBoxExtent(FVector(BoxThickness, Radius, (StraightLength + Radius) / 2));
	}
}