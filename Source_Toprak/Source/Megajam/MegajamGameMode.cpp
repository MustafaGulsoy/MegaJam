// Copyright Epic Games, Inc. All Rights Reserved.

#include "MegajamGameMode.h"
#include "MegajamCharacter.h"
#include "MyPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AMegajamGameMode::AMegajamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
