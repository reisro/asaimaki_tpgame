// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "imgui.h"
#include "ImGuiDelegates.h"
#include "AdventureGame/AdventureGameCharacter.h"

#include "AsaiMakiGameDebugger.generated.h"

UCLASS()
class ADVENTUREGAME_API AAsaiMakiGameDebugger : public AActor
{
	GENERATED_BODY()
	
public:

	bool ShowAvailableCharacterAbilities_flag;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AAdventureGameCharacter* PlayerCharacter;
	
	// Sets default values for this actor's properties
	AAsaiMakiGameDebugger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
    void ActivateMainMenuBar();

	UFUNCTION()
	void ShowAvailableCharacterAbilities();

};
