// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Collectible.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,Blueprintable)
class UCollectible : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NOTNIGHTS_API ICollectible
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Collect")
	bool OnDirectCollect();
	virtual bool OnDirectCollect_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Collect")
	bool OnLoop();
	virtual bool OnLoop_Implementation();
};
