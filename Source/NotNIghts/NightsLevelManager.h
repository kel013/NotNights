// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PathSpline.h"

#include "NightsLevelManager.generated.h"

UCLASS()
class NOTNIGHTS_API ANightsLevelManager : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Paths", meta = (AllowPrivateAccess = "true"))
	TArray<APathSpline*> Paths;
	
public:	
	// Sets default values for this actor's properties
	ANightsLevelManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	APathSpline* GetPath(int Lap);

};
