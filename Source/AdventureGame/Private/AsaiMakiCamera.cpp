// Fill out your copyright notice in the Description page of Project Settings.


#include "AsaiMakiCamera.h"

// Sets default values
AAsaiMakiCamera::AAsaiMakiCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Find the actor that handles control for the local player
	OurPlayer = UGameplayStatics::GetPlayerController(this,0);

}

void AAsaiMakiCamera::CameraCloseUp()
{
	if (OurPlayer)
	{
		if ((OurPlayer->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
		{
			UE_LOG(LogTemp, Warning, TEXT("Set Target View"));

			// Blend smoothly to camera two
			OurPlayer->SetViewTargetWithBlend(CameraTwo, 1.25f);
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("Not Set Target View"));
	}
}

// Called when the game starts or when spawned
void AAsaiMakiCamera::BeginPlay()
{
	Super::BeginPlay();

	NewDirection = CameraTwo->GetActorLocation();
	
}

// Called every frame
void AAsaiMakiCamera::Tick(float DeltaTime)
{
	const float TimeBetweenCameraChanges = 3.0f;

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
			//else

			CameraCloseUp();
		}
	}

	//NewDirection.X -= 10.0f * 10.0f * DeltaTime;
	//CameraTwo->SetActorLocation(NewDirection);
	
	Super::Tick(DeltaTime);
}

