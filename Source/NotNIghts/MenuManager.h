// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Camera/CameraActor.h"

#include "MenuManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NOTNIGHTS_API AMenuManager : public AInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ACameraActor* MenuCamera;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsActive;

public:
	//Each menu has their own manager and you can bind this Function to events to enter the menu and make the correct camera transition
	UFUNCTION(BlueprintCallable)
	void EnterMenu();
};
