// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
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
	TMap<FGameplayTag, int32> EffectContainerMap;
};
