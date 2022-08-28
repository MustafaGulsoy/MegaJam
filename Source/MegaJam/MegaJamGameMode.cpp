// Copyright Epic Games, Inc. All Rights Reserved.

#include "MegaJamGameMode.h"
#include "MegaJamCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMegaJamGameMode::AMegaJamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
