// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraTimeline.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveVector.h"

// Sets default values
ACameraTimeline::ACameraTimeline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool ACameraTimeline::ReachedEndPoint(FVector start, FVector end, FRotator startRotation, FRotator endRotation)
{
	UE_LOG(LogTemp, Warning, TEXT("Playback Position: %f"), curveTimeline.GetPlaybackPosition());
	UE_LOG(LogTemp, Warning, TEXT("Playback Position: %f"), curveTimeline.GetTimelineLength());

	//Target->SetActorRotation(start.Rotation());
	
	if (curveTimeline.GetPlaybackPosition() < curveTimeline.GetTimelineLength())
	{
		FVector FinalLocation = FMath::Lerp(start, end, curveTimeline.GetPlaybackPosition()/curveTimeline.GetTimelineLength());
	
		Target->SetActorLocation(FinalLocation);
		Target->SetActorRotation(FMath::Lerp(startRotation,endRotation,curveTimeline.GetPlaybackPosition()/curveTimeline.GetTimelineLength()));

		return false;
	}
	else
		return true;
}

// Called when the game starts or when spawned
void ACameraTimeline::BeginPlay()
{
	Super::BeginPlay();

	if(curve)
	{
		FOnTimelineVector TimelineReached;
		//TimelineReached.BindUFunction(this, FName("ReachedEndPoint"));
		curveTimeline.AddInterpVector(curve, TimelineReached);
		//curve->GetVectorValue(5.0f).Set(FVector::OneVector.X*10.0f,FVector::OneVector.X*10.0f,FVector::OneVector.X*10.0f);
	}
}

// Called every frame
void ACameraTimeline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	curveTimeline.TickTimeline(DeltaTime);
}
