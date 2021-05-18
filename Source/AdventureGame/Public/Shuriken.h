// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CinematicCamera/Public/CineCameraActor.h"
#include "Shuriken.generated.h"

UCLASS()
class ADVENTUREGAME_API AShuriken : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShuriken();

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(VisibleAnywhere)
	FVector Direction;
	
	UPROPERTY(VisibleAnywhere)
	ACineCameraActor* CineCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
