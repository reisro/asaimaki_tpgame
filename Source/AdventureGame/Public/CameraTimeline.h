// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "CameraTimeline.generated.h"

class UCurveVector;

UCLASS()
class ADVENTUREGAME_API ACameraTimeline : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	AActor* Target;

	UPROPERTY(EditAnywhere)
	FVector StartLocation;

	UPROPERTY(EditAnywhere)
	FVector EndLocation;

	FTimeline curveTimeline;
	
	// Sets default values for this actor's properties
	ACameraTimeline();

	UFUNCTION(BlueprintCallable)
	bool ReachedEndPoint();

protected:
	
	UPROPERTY(EditAnywhere, Category="Timeline")
	UCurveVector* curve;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
