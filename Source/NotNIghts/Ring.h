// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectible.h"
#include "CollectableBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Ring.generated.h"

UCLASS()
class NOTNIGHTS_API ARing : public ACollectableBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int NumberOfSections{ 12 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Radius{ 500.0f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float BoxThickness{ 5.0f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ring Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMesh* RingMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ring Mesh", meta = (AllowPrivateAccess = "true"))
	float MeshScale{ 1.0f };
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ring Mesh", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> RingStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;
public:	
	// Sets default values for this actor's properties
	ARing();
	void OnConstruction(const FTransform& Transform) override;

	virtual bool OnDirectCollect() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SetUpRingObjects();

};
