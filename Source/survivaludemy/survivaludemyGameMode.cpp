// Copyright Epic Games, Inc. All Rights Reserved.

#include "survivaludemyGameMode.h"
#include "survivaludemyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AsurvivaludemyGameMode::AsurvivaludemyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
