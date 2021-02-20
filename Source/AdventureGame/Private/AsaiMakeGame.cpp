// Fill out your copyright notice in the Description page of Project Settings.


#include "AsaiMakeGame.h"

// Sets default values
AAsaiMakeGame::AAsaiMakeGame()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAsaiMakeGame::BeginPlay()
{
	Super::BeginPlay();

	ChooseRandomBoss();
}

// Called every frame
void AAsaiMakeGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAsaiMakeGame::ChooseRandomBoss()
{
	int32 numberOfNinjas = Ninjas.Num();

	int32 NinjaID = FMath::RandRange(0,numberOfNinjas-1);

	for (AAdventureGameCharacter* Ninja : Ninjas)
		Ninja->IsNinjaBoss = true;
}

AAdventureGameCharacter* AAsaiMakeGame::GetNinjaBoss() const
{
	return Boss;
}

