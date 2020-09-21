// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
