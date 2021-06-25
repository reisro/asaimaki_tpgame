// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeRotator.generated.h"

UCLASS()
class ADVENTUREGAME_API ACubeRotator : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	float scale = 1.0f;
	
	UPROPERTY(VisibleAnywhere)
	FVector PositionAroundTarget;

	UPROPERTY(VisibleAnywhere)
	FVector PositionFromTarget;
	
	UPROPERTY(VisibleAnywhere)
	FRotator NewRotation;

	UPROPERTY(EditAnywhere)
	AActor* Target;

	UPROPERTY(EditAnywhere)
	FVector TargetPosition;
	
	// Sets default values for this actor's properties
	ACubeRotator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
