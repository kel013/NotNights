// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "PathSpline.generated.h"

UCLASS()
class NOTNIGHTS_API APathSpline : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ring Mesh", meta = (AllowPrivateAccess = "true"))
	USplineComponent* Spline;
public:	
	// Sets default values for this actor's properties
	APathSpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ARankScoreMinimum;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int BRankScoreMinimum;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int CRankScoreMinimum;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	USplineComponent* GetSpline(){ return Spline; };
};
