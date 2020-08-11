// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AsaiMakiCommonTypes.generated.h"

UENUM(BlueprintType) 
enum GameState
{
	MainMenu UMETA(DisplayName="Main Menu"),
	Playing UMETA(DisplayName="Playing"),
	End UMETA(DisplayName="End"),
	Credits UMETA(DisplayName="Credits")
};

UENUM(BlueprintType) 
enum CharacterState
{
	Alive UMETA(DisplayName="Alive"),
	Dead UMETA(DisplayName="Dead")
};

UENUM(BlueprintType) 
enum CharacterAnimationState
{
	Idle UMETA(DisplayName="Idle"),
	Walk UMETA(DisplayName="Walk"),
	Running UMETA(DisplayName="Running"),
	Combat UMETA(DisplayName="Combat"),
	Die UMETA(DisplayName="Die")
};

UENUM(BlueprintType)
enum ItemType
{
	Health UMETA(DisplayName="Health"),
	CombatXP UMETA(DisplayName="CombatXP")
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
	TEnumAsByte<ItemType> itemType;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStarts);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEnds);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAsaiMakiPicksUpItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAsaiMakiReachesCheckpoint);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAsaiMakiHitsOpponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAsaiMakiGetsHurt);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAsaiMakiDies);
