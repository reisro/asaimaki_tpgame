// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// ----------------------------------------------------------------------------------------------------------------
// A Gameplay Ability derived from the UGameplayAbility class, defines what an in-game ability does, what it costs
// to use, when or under what conditions it can be used, and so on.
// ----------------------------------------------------------------------------------------------------------------

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AsaiMakiAbilityTypes.h"
#include "NinjaGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREGAME_API UNinjaGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

	public:
	UNinjaGameplayAbility();

	/** Map of gameplay tags to gameplay effect containers */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffects)
	TMap<FGameplayTag, FAsaiMakiGameplayEffectContainer> EffectContainerMap;
};
