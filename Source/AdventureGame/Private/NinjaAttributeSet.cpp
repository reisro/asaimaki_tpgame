// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaAttributeSet.h"
#include "AdventureGame/AdventureGameCharacter.h"
#include "NinjaGameplayAbility.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UNinjaAttributeSet::UNinjaAttributeSet():
Health(100)
{
}

void UNinjaAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
    UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();

    /// Get the Target actor, which should be our owner
    AActor* TargetActor = nullptr;
    AController* TargetController = nullptr;
    AAdventureGameCharacter* TargetCharacter = nullptr;

    if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
    {
        TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
        TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
        TargetCharacter = Cast<AAdventureGameCharacter>(TargetActor);
    }
    
    if (Data.EvaluatedData.Attribute == GetDamageAttribute())
    {
        // Get the Source actor
        AActor* SourceActor = nullptr;
        AController* SourceController = nullptr;
        AAdventureGameCharacter* SourceCharacter = nullptr;
        
        if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
        {
            SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
            SourceController = Source->AbilityActorInfo->PlayerController.Get();
            if (SourceController == nullptr && SourceActor != nullptr)
            {
                if (APawn* Pawn = Cast<APawn>(SourceActor))
                {
                    SourceController = Pawn->GetController();
                }
            }

            // Use the controller to find the source pawn
            if (SourceController)
            {
                SourceCharacter = Cast<AAdventureGameCharacter>(SourceController->GetPawn());
            }
            else
            {
                SourceCharacter = Cast<AAdventureGameCharacter>(SourceActor);
            }

            // Set the causer actor based on context if it's set
            if (Context.GetEffectCauser())
            {
                SourceActor = Context.GetEffectCauser();
            }
        }

        const float LocalDamage = GetDamage();
        SetDamage(0.f);
    }
}

void UNinjaAttributeSet::OnRep_Health()
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UNinjaAttributeSet, Health);
}
