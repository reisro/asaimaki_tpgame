
// Base class  Character, designed to be inherited from player and NPC characters
// Asai Maki Demo Project v1.0
// Rodrigo Reis

#pragma once

#include <string>

#include "AsaiMaki_TPGame.h"
#include "AsaiMakiFootCollision.h"
#include "AsaiMakiAnimInstance.h"
#include "NinjaAbilitySystemComponent.h"
#include "NinjaAttributeSet.h"
#include "AbilitySystemInterface.h"
#include "NinjaGameplayAbility.h"
#include "GameFramework/Character.h"
#include "GameFramework/CheatManager.h"
#include "AdventureGameCharacter.generated.h"

class AsaiMakiFootCollision;

UCLASS(config=Game)
class AAdventureGameCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Left Foot Socket to simulate collision against left foot character animations */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sockets Collision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* LeftFootSocket;

	/** Left Foot Socket to simulate collision against left foot character animations */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sockets Collision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* RightFootSocket;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Anim Instance */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UAsaiMakiAnimInstance* AsaiMakiAnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UAsaiMakiAnimInstance* NinjaAnimInstance;

	public:

	AAdventureGameCharacter();

	// Overrides
	virtual void PossessedBy(AController* NewController) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Effects")
	float Slowmotion = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Effects")
	UCheatManager* CheatManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Effects")
	TSubclassOf<UCheatManager> CheatClass;

	class FootCollisionComponent* RFootCollision;

	class FootCollisionComponent* LFootCollision;

	// a fast data access to the collision class
	TWeakObjectPtr<AsaiMakiFootCollision> rightFootCollision;

	// a fast data access to the collision class
	TWeakObjectPtr<AsaiMakiFootCollision> leftFootCollision;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

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

	int GetGameplayAbilities() const;

	FString GetGameplayAbilityName() const;

	UFUNCTION()
	void BeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ninja")
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	int32 NinjaLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	int32 bAbilitesInitialized;

	UPROPERTY()
	UNinjaAbilitySystemComponent* NinjaAbilitySystem;

	UPROPERTY(VisibleAnywhere)
	UNinjaAttributeSet* NinjaAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Abilities")
	TArray<TSubclassOf<UNinjaGameplayAbility>> GameplayAbilities;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	//TMap<FAsaiMakiNinjaItem, TSubclassOf<UNinjaGameplayAbility>> MapAbilities;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	//TMap<FAsaiMakiNinjaItem, FGameplayAbilitySpecHandle> MapAbilitiesHandle;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};