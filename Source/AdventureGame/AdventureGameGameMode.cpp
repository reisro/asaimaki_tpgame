// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AdventureGameGameMode.h"
#include "AdventureGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAdventureGameGameMode::AAdventureGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Blueprints/AsaiMaki_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AAdventureGameGameMode::BeginPlay()
{
	//AActor* pawn = Cast<AActor>(DefaultPawnClass->GetDefaultSubobjectByName("DefaultPawn"));
	//pawn->SetActorLocation(FVector::ZeroVector);
}

void AAdventureGameGameMode::Tick(float DeltaSeconds)
{
	if (HasMatchStarted())
	{
		AActor* pawn = Cast<AActor>(DefaultPawnClass->GetDefaultSubobjectByName("DefaultPawn"));

		UE_LOG(LogTemp, Warning, TEXT("Not null"));
	}
}
