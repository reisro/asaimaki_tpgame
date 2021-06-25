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
	float YawValue= (Target->GetActorLocation()-GetActorLocation()).Rotation().Yaw;

	NewDirection = Target->GetActorLocation()-FVector::ForwardVector*250.0f;//+FVector(pitchValue*scale, rollValue*scale, GetActorLocation().Z);
	NewRotation = FRotator(.0f, YawValue, .0f);

	SetActorLocation(NewDirection);
	SetActorRotation(NewRotation);
}

