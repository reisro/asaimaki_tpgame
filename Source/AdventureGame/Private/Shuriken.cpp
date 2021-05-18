// Fill out your copyright notice in the Description page of Project Settings.


#include "Shuriken.h"

// Sets default values
AShuriken::AShuriken()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShuriken::BeginPlay()
{
	Super::BeginPlay();

	Direction = FVector::ForwardVector + GetActorLocation();
}

// Called every frame
void AShuriken::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Direction.X -= DisplacementSpeed * 10.0f * DeltaTime;
	Rotation.Yaw += DeltaTime * RotationSpeed * 2.0f;
	
	SetActorLocationAndRotation(Direction, Rotation);
}