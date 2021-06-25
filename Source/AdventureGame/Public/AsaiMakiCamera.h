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

	UPROPERTY(VisibleAnywhere)
	FVector NewDirection;

	UPROPERTY(VisibleAnywhere)
	FRotator NewRotation;

	APlayerController* OurPlayer;

	UPROPERTY(EditAnywhere)
	float TimeToChangeCamera;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* CameraOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* CameraCombat;
	
	// Sets default values for this actor's properties
	AAsaiMakiCamera();

	UFUNCTION(BlueprintCallable)
	void CameraCloseUp(float blendTime);

	UFUNCTION(BlueprintCallable)
    void CameraThreeSixtyRound(float blendTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
