// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NinjaGameplayAbility.h"
#include "Engine/DataAsset.h"
#include "AsaiMakiItem.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class ADVENTUREGAME_API UAsaiMakiItem : public UPrimaryDataAsset
{
	GENERATED_BODY()

	public:
	UAsaiMakiItem():
	CombatXPNeeded(0),
    AbilityLevel(1)
	{}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item")
	FPrimaryAssetType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	int32 CombatXPNeeded;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Abilities")
	TSubclassOf<UNinjaGameplayAbility> GrantedAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Abilities")
	int32 AbilityLevel;

	/** Overridden to use saved type */
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
