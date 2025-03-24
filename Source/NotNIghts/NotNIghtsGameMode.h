// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NotNIghtsGameMode.generated.h"

UCLASS(minimalapi)
class ANotNIghtsGameMode : public AGameModeBase
{
	GENERATED_BODY()

	/** Pathing with Spline */
	UPROPERTY(EditAnywhere)
	AActor* Path;

public:
	ANotNIghtsGameMode();


};



