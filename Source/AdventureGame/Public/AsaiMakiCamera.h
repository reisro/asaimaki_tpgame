// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "AsaiMakiCamera.generated.h"

UCLASS()
class ADVENTUREGAME_API AAsaiMakiCamera : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	AActor* CameraOne;

	UPROPERTY(EditAnywhere)
	AActor* CameraTwo;

	UPROPERTY(VisibleAnywhere)
	FVector NewDirection;

	APlayerController* OurPlayer;

	UPROPERTY(EditAnywhere)
	float TimeToChangeCamera;
	
public:	
	// Sets default values for this actor's properties
	AAsaiMakiCamera();

	UFUNCTION(BlueprintCallable)
	void CameraCloseUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
