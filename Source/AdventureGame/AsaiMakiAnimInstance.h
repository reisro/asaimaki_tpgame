// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AsaiMakiAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREGAME_API UAsaiMakiAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAsaiMakiAnimInstance();

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable)
	float GetSpeed() const { return Speed; }

	UFUNCTION(BlueprintCallable)
	bool IsInAir() const { return isInAir; }

	UFUNCTION(BlueprintCallable)
	bool CanKick() const { return canKick; }

	UFUNCTION(BlueprintCallable)
	bool IsHit() const { return isHit; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	bool isInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	bool canKick;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	bool isHit;
};
