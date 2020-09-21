// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaAbilitySystemComponent.h"

UNinjaAbilitySystemComponent::UNinjaAbilitySystemComponent()
{
}

void UNinjaAbilitySystemComponent::GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer,
    TArray<UNinjaGameplayAbility*>& ActiveAbilities)
{
    TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
    GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, AbilitiesToActivate, false);

    for (FGameplayAbilitySpec* Spec:AbilitiesToActivate)
    {
        TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();

        for (UGameplayAbility* ActiveAbility: AbilityInstances)
        {
            ActiveAbilities.Add(Cast<UNinjaGameplayAbility>(ActiveAbility));
            UE_LOG(LogTemp, Warning, TEXT("Number of Active Abilities %d"), ActiveAbilities.Num());
        }
    }
}

int32 UNinjaAbilitySystemComponent::GetDefaultAbilityLevel() const
{
    return 0;
}


