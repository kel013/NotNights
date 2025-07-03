// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Deposit.generated.h"

UCLASS()
class NOTNIGHTS_API ADeposit : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;
	
public:	
	// Sets default values for this actor's properties
	ADeposit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void DepositEssentials();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
