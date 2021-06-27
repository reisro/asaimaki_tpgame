// Fill out your copyright notice in the Description page of Project Settings.


#include "AsaiMakiCamera.h"

// Sets default values
AAsaiMakiCamera::AAsaiMakiCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAsaiMakiCamera::CameraCloseUp(float blendTime)
{
	if ((OurPlayer->GetViewTarget() != CameraCombat) && (CameraCombat != nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("Set Target View"));
		
		// Blend smoothly to camera two
		OurPlayer->SetViewTargetWithBlend(CameraCombat, blendTime);
	}
}

void AAsaiMakiCamera::CameraThreeSixtyRound(float blendTime)
{
	float elapsedTime = GetGameTimeSinceCreation()-3.0f;
	float pitchValue = FMath::Cos(elapsedTime);
	float rollValue = FMath::Sin(elapsedTime);
	
	PositionFromTarget = Target->GetActorLocation()-FVector::ForwardVector*250.0f;
	PositionAroundTarget = FVector(pitchValue*scaleDistance+Target->GetActorLocation().X,
		rollValue*scaleDistance+Target->GetActorLocation().Y, CameraCombat->GetActorLocation().Z);

	float YawValue= (Target->GetActorLocation()-CameraCombat->GetActorLocation()).Rotation().Yaw;

	CameraRotation = FRotator(.0f, YawValue, .0f);
	
	CameraCombat->SetActorLocationAndRotation(PositionAroundTarget, CameraRotation);

	// Blend smoothly to camera two
	OurPlayer->SetViewTargetWithBlend(CameraCombat, blendTime);
}

// Called when the game starts or when spawned
void AAsaiMakiCamera::BeginPlay()
{
	Super::BeginPlay();
	
	// Find the actor that handles control for the local player
    OurPlayer = UGameplayStatics::GetPlayerController(this,0);
}

// Called every frame
void AAsaiMakiCamera::Tick(float DeltaTime)
{
	const float TimeBetweenCameraChanges = 2.0f;

	const float SmoothBlendTime = 1.25f;

	TimeToChangeCamera -= 0.05f;

	if (TimeToChangeCamera <= 0.0f)
	{
		TimeToChangeCamera += TimeBetweenCameraChanges;

		if (OurPlayer)
		{
			//if ((OurPlayer->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
			//{
				// Cut to camera one
				//OurPlayer->SetViewTarget(CameraOne);
			//}
		}
	}
	
	Super::Tick(DeltaTime);
}

