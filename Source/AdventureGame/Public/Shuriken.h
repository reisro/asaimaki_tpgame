// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Shuriken.generated.h"

UCLASS()
class ADVENTUREGAME_API AShuriken : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShuriken();

	UPROPERTY(EditAnywhere)
	float DisplacementSpeed;

	UPROPERTY(EditAnywhere)
	float RotationSpeed;

	UPROPERTY(VisibleAnywhere)
	FVector Direction;

	UPROPERTY(VisibleAnywhere)
	FRotator Rotation;

	UPROPERTY(EditAnywhere)
	AActor* Target;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetTarget(AActor* actor);

	UFUNCTION(BlueprintCallable)
	void CalculateDirection();

	UFUNCTION(BlueprintCallable)
	void Throw(float DeltaTime);

};
