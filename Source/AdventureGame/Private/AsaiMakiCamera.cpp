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

void AAsaiMakiCamera::CameraFollowPoints(FVector point, FVector direction, float deltaTime, float blendTime)
{
	distanceCameraFromTarget = (Target->GetActorLocation()-CameraCombat->GetActorLocation()).Size();
	
	if ( distanceCameraFromTarget > 0.01f)
	{
		FVector moveCamera = Target->GetActorLocation()-CameraCombat->GetActorLocation();
		
		UE_LOG(LogTemp, Warning, TEXT("CameraCombat position: (%f,%f,%f)"), CameraCombat->GetActorLocation().X, CameraCombat->GetActorLocation().Y, CameraCombat->GetActorLocation().Z);

		FTTranslation.SetTranslation(FVector(CameraCombat->GetActorLocation() + moveCamera.GetSafeNormal() * 60.0f * deltaTime));

		CameraCombat->SetActorTransform(FTTranslation);
		CameraCombat->SetActorRotation((DirectionTarget->GetActorLocation()-Target->GetActorLocation()).Rotation());
	
		// Blend smoothly to camera two
		OurPlayer->SetViewTargetWithBlend(CameraCombat, blendTime);
	}
}

void AAsaiMakiCamera::CameraFollowTransform(TMap<FVector, FRotator> cameraTransform, int keyframes, float blendTime, float deltaTime, bool followThrough)
{
	// Blend smoothly to camera combat
	OurPlayer->SetViewTargetWithBlend(CameraCombat, blendTime);
	
	// Feed the class map with input map
	TransformPaths = cameraTransform;

	// Get the size of the map
	keyframes = cameraTransform.Num();

	int followThroughId = 0;

	// translate the camera through all points matching the camera transforms
	for (auto& Transform: TransformPaths)
	{
		FollowThroughStart.Add(Transform.Key);
		RotationThroughStart.Add(Transform.Value);
	}

	for (size_t i=0; i<FollowThroughStart.Num()-1; i++)
		FollowThroughEnd.Add(FollowThroughStart[i+1]);

	for (size_t i=0; i<RotationThroughStart.Num()-1; i++)
		RotationThroughEnd.Add(RotationThroughStart[i+1]);
	
	float distanceFromTarget = 0.0f;

	FVector finalLocation = TargetRefPosition+FollowThroughStart[followThroughId];

	while (!followThrough)
	{
		CameraCombat->SetActorLocationAndRotation(finalLocation, RotationThroughStart[followThroughId]);
		
		/*distanceFromTarget = (FollowThroughEnd[followThroughId]-FollowThroughStart[followThroughId]).Size();

		if (distanceFromTarget > 0.1f)
		{
			FVector difference = FollowThroughEnd[followThroughId]-FollowThroughStart[followThroughId];
			FVector moveCamera = CameraCombat->GetActorLocation() + difference;

			FTTranslation.SetTranslation(moveCamera.GetSafeNormal() * 20.0f * deltaTime);
			FTTranslation.SetRotation(FRotator(RotationThroughEnd[followThroughId+1]).Quaternion());
			CameraCombat->SetActorRotation(FMath::Lerp(CameraCombat->GetActorRotation(), difference.Rotation(),0.2f));
		}*/
		
		//if (followThroughId < TransformPaths.Num())
			//followThroughId++;
		//else
		followThrough = true;
	}
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

	TargetRefPosition = Target->GetActorLocation();
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

