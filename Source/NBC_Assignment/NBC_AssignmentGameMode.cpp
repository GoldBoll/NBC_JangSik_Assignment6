// Copyright Epic Games, Inc. All Rights Reserved.

#include "NBC_AssignmentGameMode.h"
#include "NBC_AssignmentCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANBC_AssignmentGameMode::ANBC_AssignmentGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
