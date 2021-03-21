// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NinjaCharacter.h"
#include "MaleNPCNinja.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREGAME_API AMaleNPCNinja : public ANinjaCharacter
{
	GENERATED_BODY()

	public:
	AMaleNPCNinja();

	protected:

	UFUNCTION(BlueprintCallable)
	virtual void SetupBodyCollidersName() override;
};
