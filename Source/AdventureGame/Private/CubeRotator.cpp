// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeRotator.h"

// Sets default values
ACubeRotator::ACubeRotator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACubeRotator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeRotator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FollowWayPoints(DeltaTime);

	/*float elapsedTime = GetGameTimeSinceCreation();
	float pitchValue = FMath::Cos(elapsedTime);
	float rollValue = FMath::Sin(elapsedTime);

	PositionFromTarget = Target->GetActorLocation()-FVector::ForwardVector*250.0f;
	PositionAroundTarget = FVector(pitchValue*scale+Target->GetActorLocation().X, rollValue*scale+Target->GetActorLocation().Y, GetActorLocation().Z);
	
	float YawValue= (Target->GetActorLocation()-GetActorLocation()).Rotation().Yaw;

	NewRotation = FRotator(.0f, YawValue, .0f);

	SetActorLocation(PositionAroundTarget);
	SetActorRotation(NewRotation);*/
}

void ACubeRotator::FollowWayPoints(float deltaTime)
{
	if (FVector(Target->GetActorLocation() - GetActorLocation()).Size() > 0.1f)
	{
		FVector moveCube = Target->GetActorLocation() - GetActorLocation();
		
		UE_LOG(LogTemp, Warning, TEXT("%f"), GetGameTimeSinceCreation());
		UE_LOG(LogTemp, Warning, TEXT("CameraCombat position: (%f,%f,%f)"), Target->GetActorLocation().X, Target->GetActorLocation().Y, Target->GetActorLocation().Z);

		FTTranslation.SetTranslation(FVector(GetActorLocation()+moveCube.GetSafeNormal()*20.0f*deltaTime));

		this->SetActorTransform(FTTranslation);
		this->SetActorRotation((Target->GetActorLocation() - GetActorLocation()).Rotation());
	}
}

