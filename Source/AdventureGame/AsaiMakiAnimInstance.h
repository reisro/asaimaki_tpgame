// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
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
	bool IsInAir() const { return InAir; }
	
	UFUNCTION(BlueprintCallable)
    bool IsKnockedDown() const { return IsDown; }

	UFUNCTION(BlueprintCallable)
	bool IsKicking() const { return Kicking; }

	UFUNCTION(BlueprintCallable)
	void CanKick() { EnableKick = !EnableKick; Kicking = !Kicking; }

	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdateAnimationProperties(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void PlayKickAttack();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	bool InAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animation)
	bool IsDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	bool EnableKick;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animation)
	bool Kicking;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animation)
	bool Attacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	bool Hit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class APawn* Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class ANinjaCharacter* Character;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat)
	class UAnimMontage* KickAttackAnimMontage;
};
