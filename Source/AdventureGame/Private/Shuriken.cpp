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

	Direction.X -= Speed * 10.0f * DeltaTime;
	SetActorLocation(Direction);
}

