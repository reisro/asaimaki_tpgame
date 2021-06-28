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
	FRotator CameraRotation;

	APlayerController* OurPlayer;

	UPROPERTY(EditAnywhere)
	float TimeToChangeCamera;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* CameraMain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* CameraCombat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Target;

	UPROPERTY(VisibleAnywhere)
	FVector PositionFromTarget;

	UPROPERTY(EditAnywhere)
	FVector PositionAroundTarget;

	UPROPERTY(EditAnywhere)
	float scaleDistance = 1.0f;
	
	// Sets default values for this actor's properties
	AAsaiMakiCamera();

	UFUNCTION(BlueprintCallable)
	void CameraCloseUp(float blendTime);

	UFUNCTION(BlueprintCallable)
    void CameraThreeSixtyRound(float elapsedTime, float blendTime);
	
	UFUNCTION(BlueprintCallable)
    void CameraFollowPoints(FVector point, FVector direction, float blendTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
