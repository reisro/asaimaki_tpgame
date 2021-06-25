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

	float elapsedTime = GetGameTimeSinceCreation();
	float pitchValue = FMath::Cos(elapsedTime);
	float rollValue = FMath::Sin(elapsedTime);

	PositionFromTarget = Target->GetActorLocation()-FVector::ForwardVector*250.0f;
	PositionAroundTarget = FVector(pitchValue*scale+Target->GetActorLocation().X, rollValue*scale+Target->GetActorLocation().Y, GetActorLocation().Z);
	
	float YawValue= (Target->GetActorLocation()-GetActorLocation()).Rotation().Yaw;

	NewRotation = FRotator(.0f, YawValue, .0f);

	SetActorLocation(PositionAroundTarget);
	SetActorRotation(NewRotation);
}

