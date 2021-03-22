// Fill out your copyright notice in the Description page of Project Settings.


#include "MaleNPCNinja.h"

AMaleNPCNinja::AMaleNPCNinja():ANinjaCharacter()
{
    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;
}

void AMaleNPCNinja::SetupBodyCollidersName()
{    
    LeftHandBoneName = FName(TEXT("hand_l"));
    RightHandBoneName = FName(TEXT("hand_r"));
    LeftFootBoneName = FName(TEXT("foot_l"));
    RightFootBoneName = FName(TEXT("foot_r"));
}
