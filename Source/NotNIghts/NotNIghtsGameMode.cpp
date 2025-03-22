// Copyright Epic Games, Inc. All Rights Reserved.

#include "NotNIghtsGameMode.h"
#include "NotNIghtsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANotNIghtsGameMode::ANotNIghtsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
