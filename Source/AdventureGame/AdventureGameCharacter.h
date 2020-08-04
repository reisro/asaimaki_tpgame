// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AsaiMakiFootCollision.h"
#include "AsaiMakiAnimInstance.h"
#include "AdventureGameCharacter.generated.h"

class AsaiMakiFootCollision;

UCLASS(config=Game)
class AAdventureGameCharacter : public ACharacter
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

	public:
	AAdventureGameCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Anim Instance */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAsaiMakiAnimInstance* asaiMakiAnimInstance;

	class FootCollisionComponent* RFootCollision;

	class FootCollisionComponent* LFootCollision;

	// a fast data access to the collision class
	TWeakObjectPtr<AsaiMakiFootCollision> rightFootCollision;

	// a fast data access to the collision class
	TWeakObjectPtr<AsaiMakiFootCollision> leftFootCollision;

	UFUNCTION()
	void BeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

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