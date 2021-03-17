// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AdventureGame/AsaiMaki_TPGame.h"
#include "AdventureGame/AsaiMakiAnimInstance.h"
#include "AdventureGame/AsaiMakiFootCollision.h"
#include "NinjaAbilitySystemComponent.h"
#include "NinjaAttributeSet.h"
#include "AbilitySystemInterface.h"
#include "NinjaGameplayAbility.h"
#include "GameFramework/Character.h"
#include "GameFramework/CheatManager.h"
#include "NinjaCharacter.generated.h"

using namespace std;

UCLASS(config=Game)
class ADVENTUREGAME_API ANinjaCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Left Hand Socket to simulate collision against left foot character animations */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sockets Collision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* LeftHandCollider;

	/** Right Hand Socket to simulate collision against left foot character animations */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sockets Collision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* RightHandCollider;
	
	/** Left Foot Socket to simulate collision against left foot character animations */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sockets Collision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* LeftFootCollider;

	/** Left Foot Socket to simulate collision against left foot character animations */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sockets Collision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* RightFootCollider;

	// Anim instance class
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UAsaiMakiAnimInstance* NinjaAnimInstance;

public:
	
	// Sets default values for this character's properties
	ANinjaCharacter();

	virtual void PossessedBy(AController* NewController) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
    int32 GetHealth() const;

	UFUNCTION(BlueprintCallable)
    void SetHealth(int32 _health);

	UFUNCTION(BlueprintCallable, Category="Abilities")
    void ActivateStartupNinjaAbility();

	UFUNCTION(BlueprintCallable, Category = "Abilities")
    void GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags, TArray<UNinjaGameplayAbility*>& ActiveAbilities);

	UFUNCTION(BlueprintCallable, Category="Abilities")
    bool ActivateAbilitiesWithTag(FGameplayTagContainer AbilityTag, bool bAllowRemoteActivation = true);

	UFUNCTION(BlueprintCallable, Category="Abilities")
	int GetGameplayAbilities() const;

	UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDamaged(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ANinjaCharacter* InstigatorCharacter, AActor* DamageCauser);

	UFUNCTION()
    virtual void BeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnHealthDamage(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	UFUNCTION()
	virtual void OnHitDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ANinjaCharacter* InstigatorCharacter, AActor* DamageCauser);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ninja")
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	int32 NinjaLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	int32 AbilitiesInitialized;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	int32 bAbilitesInitialized;

	UPROPERTY()
	UNinjaAbilitySystemComponent* NinjaAbilitySystem;

	UPROPERTY(VisibleAnywhere)
	UNinjaAttributeSet* NinjaAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Abilities")
	TArray<TSubclassOf<UNinjaGameplayAbility>> GameplayAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Abilities")
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};