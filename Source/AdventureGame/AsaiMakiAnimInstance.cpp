// Fill out your copyright notice in the Description page of Project Settings.


#include "AsaiMakiAnimInstance.h"
#include "AdventureGameCharacter.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"

UAsaiMakiAnimInstance::UAsaiMakiAnimInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("Created Asai Maki Anim Instance"));
}

void UAsaiMakiAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();

		if (Pawn)
			Character = Cast<AAdventureGameCharacter>(Pawn);
	}
}

void UAsaiMakiAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (Pawn == nullptr)
		Pawn = TryGetPawnOwner();

	if (Pawn)
	{
		FVector PawnVelocity = Pawn->GetVelocity();
		FVector RightSpeed = FVector(PawnVelocity.X, PawnVelocity.Y, 0.f);
		this->Speed = RightSpeed.Size();

		this->InAir = Pawn->GetMovementComponent()->IsFalling();
	}
}

void UAsaiMakiAnimInstance::PlayKickAttack()
{
}
