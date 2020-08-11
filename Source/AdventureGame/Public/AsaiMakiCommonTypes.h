// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AsaiMakiCommonTypes.generated.h"

enum class GameState
{
	MainMenu,
	Playing,
	End,
	Credits
};

enum class CharacterState
{
	Alive,
	Dead
};

enum class CharacterAnimationState
{
	Idle,
	Walk,
	Running,
	Combat,
	Die
};

enum class ItemType
{
	Health,
	CombatXP
};

USTRUCT(BlueprintType)
struct ADVENTUREGAME_API FAsaiMakiItem
{
	GENERATED_BODY()
		
	// The name of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	FString name;
	
	// Quick description of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	FString desc;
	
	// Type of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	ItemType itemType;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStarts);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEnds);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAsaiMakiPicksUpItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAsaiMakiReachesCheckpoint);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAsaiMakiHitsOpponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAsaiMakiGetsHurt);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAsaiMakiDies);
