// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraSystemDataIO.h"
#include "CameraSystemDataIO.h"
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

	CameraSystemDataIO* cameraSystemDataIO;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* CameraMain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* CameraCombat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Target;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* DirectionTarget;

	UPROPERTY(VisibleAnywhere)
	TMap<FVector,FRotator> TransformPaths;

	UPROPERTY(VisibleAnywhere)
	TArray<FVector> FollowThroughStart;
	
	UPROPERTY(VisibleAnywhere)
	TArray<FVector> FollowThroughEnd;

	UPROPERTY(VisibleAnywhere)
	TArray<FRotator> RotationThroughStart;
	
	UPROPERTY(VisibleAnywhere)
	TArray<FRotator> RotationThroughEnd;

	UPROPERTY(VisibleAnywhere)
	FVector TargetRefPosition;
	
	UPROPERTY(VisibleAnywhere)
	FVector PositionFromTarget;

	UPROPERTY(EditAnywhere)
	FVector PositionAroundTarget;

	FTransform FTTranslation;

	UPROPERTY(EditAnywhere)
	float scaleDistance = 1.0f;

	UPROPERTY(VisibleAnywhere)
	float distanceCameraFromTarget;
	
	// Sets default values for this actor's properties
	AAsaiMakiCamera();

	UFUNCTION(BlueprintCallable)
	void CameraCloseUp(float blendTime);

	UFUNCTION(BlueprintCallable)
    void CameraThreeSixtyRound(float elapsedTime, float blendTime);
	
	UFUNCTION(BlueprintCallable)
    void CameraFollowPoints(FVector point, FVector direction, float deltaTime, float blendTime);

	UFUNCTION(BlueprintCallable)
	void CameraFollowTransform(TMap<FVector, FRotator> cameraTransform, int keyframes, float blendTime, float deltaTime, bool followThrough);

	UFUNCTION(BlueprintCallable)
	void ShowProjectDirectory();

	UFUNCTION(BlueprintCallable)
    void CreateCameraTransformDataFile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
