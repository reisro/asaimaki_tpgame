// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// --------------------------------------------------------------------------------------------------------------------
// The Ability System Component is used for implementing, designing and building abilities and attributes for a game
// character. Any actor that interacts with the Gameplay Ability must have an Ability System Component.
// Before an actor can use an ability, the ability system component must be granted that Ability.
//
// GiveAbility: specifies the ability to add with an FGameplayAbilitySpec, and returns an FGameplayAbilitySpecHandle
// GiveAbilityAndActivateOnce: specifies the ability to add with an FGameplayAbilitySpec, and returns an FGameplayAbilitySpecHandle
// ClearAbility: TBD
// SetRemoveAbilityOnEnd: TBD
// CleanAllAbilities: TBD
// --------------------------------------------------------------------------------------------------------------------

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "NinjaGameplayAbility.h"

#include "NinjaAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREGAME_API UNinjaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UNinjaAbilitySystemComponent();

	/** Returns a list of currently active ability instances that match the tags */
	void GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<UNinjaGameplayAbility*>& ActiveAbilities);

	int32 GetDefaultAbilityLevel() const;
	
};
