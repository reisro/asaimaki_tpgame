// Fill out your copyright notice in the Description page of Project Settings.


#include "AsaiMakiCamera.h"

// Sets default values
AAsaiMakiCamera::AAsaiMakiCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraSystemDataIO = new CameraSystemDataIO();
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

void AAsaiMakiCamera::CameraThreeSixtyRound(float elapsedTime, float blendTime)
{
	float elapsedTimeCameraActive = elapsedTime-GetGameTimeSinceCreation();

	elapsedTimeCameraActive < .0f ? elapsedTimeCameraActive *= -1.0f: elapsedTimeCameraActive *= 1.0f;

	UE_LOG(LogTemp, Warning, TEXT("%f"), elapsedTimeCameraActive);
	
	float pitchValue = FMath::Cos(elapsedTimeCameraActive);
	float rollValue = FMath::Sin(elapsedTimeCameraActive);
	
	PositionFromTarget = Target->GetActorLocation()-FVector::ForwardVector*250.0f;
	PositionAroundTarget = FVector(pitchValue*scaleDistance+Target->GetActorLocation().X,
		rollValue*scaleDistance+Target->GetActorLocation().Y, CameraCombat->GetActorLocation().Z);

	float YawValue = (Target->GetActorLocation()-CameraCombat->GetActorLocation()).Rotation().Yaw;

	CameraRotation = FRotator(.0f, YawValue, .0f);
	
	CameraCombat->SetActorLocationAndRotation(PositionAroundTarget, CameraRotation);

	// Blend smoothly to camera two
	OurPlayer->SetViewTargetWithBlend(CameraCombat, blendTime);
}

void AAsaiMakiCamera::CameraFollowPoints(float deltaTime, float blendTime)
{
	if(!cameraTimeline->curveTimeline.IsPlaying())
		PlayTimelineVector();

	// Blend smoothly to camera two
	OurPlayer->SetViewTargetWithBlend(CameraCombat, blendTime);

	if(cameraTimeline->ReachedEndPoint(FollowThroughStart[followThroughId],FollowThroughEnd[followThroughId]
		,RotationThroughStart[followThroughId], RotationThroughEnd[followThroughId]))
	{
		UE_LOG(LogTemp, Warning, TEXT("Reached end point"));

		float blend = 0.0f;
		
		OurPlayer->SetViewTarget(CameraMain);
	}
}

void AAsaiMakiCamera::FeedCameraTransform(TMap<FVector, FRotator> cameraTransform)
{
	// Feed the class map with input map
	TransformPaths = cameraTransform;

	// translate the camera through all points matching the camera transforms (location, rotation)
	for (auto& Transform: TransformPaths)
	{
		FollowThroughStart.Add(TargetRefPosition+Transform.Key);
		RotationThroughStart.Add(Transform.Value);
	}

	for (size_t i=0; i<FollowThroughStart.Num()-1; i++)
        FollowThroughEnd.Add(FollowThroughStart[i+1]);

	for (size_t i=0; i<RotationThroughStart.Num()-1; i++)
		RotationThroughEnd.Add(RotationThroughStart[i+1]);
}

void AAsaiMakiCamera::UpdateCameraTransform(TArray<FVector> CameraRelativePosition)
{
	for (size_t i=0; i<FollowThroughStart.Num()-1; i++)
	{
		FollowThroughStart[i] = TargetRefPosition+CameraRelativePosition[i];
		FollowThroughEnd[i] =	TargetRefPosition+CameraRelativePosition[i+1];
	}
}

void AAsaiMakiCamera::CameraFollowTransform(TMap<FVector, FRotator> cameraTransform, int keyframes, float blendTime, float deltaTime, bool followThrough)
{
	// Blend smoothly to camera combat
	OurPlayer->SetViewTargetWithBlend(CameraCombat, blendTime);
	
	// Get the size of the map
	keyframes = cameraTransform.Num()-1;
	
	while (!followThrough)
	{
		CameraCombat->SetActorLocationAndRotation(FollowThroughStart[followThroughId], RotationThroughStart[followThroughId]);
		
		distanceCameraFromTarget = (FollowThroughEnd[followThroughId]-FollowThroughStart[followThroughId]).Size();

		UE_LOG(LogTemp, Warning, TEXT("Distance From Player: %f"), distanceCameraFromTarget);

		if (distanceCameraFromTarget > 0.1f)
		{
			FVector difference = FollowThroughEnd[followThroughId]-CameraCombat->GetActorLocation();
			FVector moveCamera = CameraCombat->GetActorLocation() + difference;

			FTTranslation.SetTranslation(moveCamera.GetSafeNormal() * 20.0f * deltaTime);
			//FTTranslation.SetRotation(FRotator(RotationThroughEnd[followThroughId+1]).Quaternion());
			CameraCombat->SetActorRotation(FMath::Lerp(CameraCombat->GetActorRotation(), RotationThroughEnd[followThroughId],0.2f));
		}
		else
			advanceKeyframe = true;

		if(advanceKeyframe)
		{
			UE_LOG(LogTemp, Warning, TEXT("Advanced keyframe"));
			
			followThrough = true;
		}

		UE_LOG(LogTemp, Warning, TEXT("Follow through id: %d"), followThroughId);
	}
}

void AAsaiMakiCamera::PlayTimelineVector()
{
	cameraTimeline->curveTimeline.Play();
}

void AAsaiMakiCamera::ShowProjectDirectory()
{
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectDirectory: %s"), *cameraSystemDataIO->GetProjectDirectory());
}

void AAsaiMakiCamera::CreateCameraTransformDataFile()
{
	cameraSystemDataIO->CreateFile();
}

// Called when the game starts or when spawned
void AAsaiMakiCamera::BeginPlay()
{
	Super::BeginPlay();
	
	// Find the actor that handles control for the local player
    OurPlayer = UGameplayStatics::GetPlayerController(this,0);

	followThroughId = 0;
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

		TargetRefPosition = Target->GetActorLocation();
	}
	
	Super::Tick(DeltaTime);
}

