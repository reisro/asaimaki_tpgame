// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AdventureGame/AdventureGameCharacter.h"
#include "GameFramework/Actor.h"
#include "AsaiMakeGame.generated.h"

UCLASS()
class ADVENTUREGAME_API AAsaiMakeGame : public AActor
{
	GENERATED_BODY()
	
public:	
	AAsaiMakeGame();

	UPROPERTY(EditAnywhere, Category="Characters")
	TArray< AAdventureGameCharacter* > Ninjas;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Characters")
	class AAdventureGameCharacter* Boss;

	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ChooseRandomBoss();

	UFUNCTION(BlueprintCallable)
	AAdventureGameCharacter* GetNinjaBoss() const;

};
