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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ACameraActor* MenuCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsActive;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnEnterMenu();

	UFUNCTION(BlueprintCallable)
	void EnterMenu();
};
