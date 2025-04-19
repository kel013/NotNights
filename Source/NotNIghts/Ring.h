// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Ring.generated.h"

UCLASS()
class NOTNIGHTS_API ARing : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int NumberOfSections{ 12 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Radius{ 500.0f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ring Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMesh* RingMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ring Mesh", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> RingStaticMesh;
public:	
	// Sets default values for this actor's properties
	ARing();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
