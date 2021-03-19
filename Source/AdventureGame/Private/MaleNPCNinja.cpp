// Fill out your copyright notice in the Description page of Project Settings.


#include "MaleNPCNinja.h"

AMaleNPCNinja::AMaleNPCNinja()
{
    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

    SetupBodyColliders();
}

void AMaleNPCNinja::SetupBodyColliders()
{    
    LeftHandBoneName = FName(TEXT("hand_l"));
    RightHandBoneName = FName(TEXT("hand_r"));
    LeftFootBoneName = FName(TEXT("foot_l"));
    RightFootBoneName = FName(TEXT("foot_r"));

    LeftHandCollider->SetupAttachment(GetMesh(), LeftHandBoneName);
    RightHandCollider->SetupAttachment(GetMesh(), RightHandBoneName);
    LeftFootCollider->SetupAttachment(GetMesh(), LeftFootBoneName);
    RightFootCollider->SetupAttachment(GetMesh(), RightFootBoneName);
}
