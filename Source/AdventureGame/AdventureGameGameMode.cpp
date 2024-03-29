// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AdventureGameGameMode.h"
#include "AdventureGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAdventureGameGameMode::AAdventureGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPerson_AsaiMakiCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
