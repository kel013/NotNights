// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LapParent.generated.h"

UCLASS()
class NOTNIGHTS_API ALapParent : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Laps", meta = (AllowPrivateAccess = "true"))
	int LapNumber;
public:	
	// Sets default values for this actor's properties
	ALapParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
