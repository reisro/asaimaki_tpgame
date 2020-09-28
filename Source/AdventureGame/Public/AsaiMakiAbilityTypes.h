// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "AsaiMakiAbilityTypes.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FAsaiMakiGameplayEffectContainer
{
	GENERATED_BODY()

public:
	FAsaiMakiGameplayEffectContainer(){}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameplayEffectContainer")
	TArray <TSubclassOf<UGameplayEffect>> TargetGameplayEffectClasses;
};
