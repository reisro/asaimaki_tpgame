// Fill out your copyright notice in the Description page of Project Settings.


#include "AsaiMakiFootCollision.h"

// Sets default values
UAsaiMakiFootCollision::UAsaiMakiFootCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void UAsaiMakiFootCollision::BeginPlay()
{
	Super::BeginPlay();
	
}

void UAsaiMakiFootCollision::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

