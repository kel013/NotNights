// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ring.h"
#include "HalfRing.generated.h"

/**
 * 
 */
UCLASS()
class NOTNIGHTS_API AHalfRing : public ARing
{
	GENERATED_BODY()
	// A half ring is composed of a square length with a half circle at the end
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float StraightLength{ 500.0f };
protected:
	void SetUpRingObjects() override;
};
