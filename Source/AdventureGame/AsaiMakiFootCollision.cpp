// Fill out your copyright notice in the Description page of Project Settings.


#include "AsaiMakiFootCollision.h"

// Sets default values
AAsaiMakiFootCollision::AAsaiMakiFootCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAsaiMakiFootCollision::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAsaiMakiFootCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAsaiMakiFootCollision::CreateFootCollision(const char * collisionName)
{
	// Set collision sockets
	FootCollision = CreateDefaultSubobject<UBoxComponent>(TEXT(collisionName));

	// Create rules for attaching sockets on components
	FAttachmentTransformRules transformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);

	FootCollision->AttachToComponent(RootComponent, transformRules, FName(TEXT("RightFoot")));

	// Create a transform that holds location, rotation and scale of collision components
	FTransform fTransform;

	// Set Location
	fTransform.SetLocation(FVector(-25.07f, 20.87f, -94.78f));

	// Set Rotator with float values
	FRotator RightCollisionRotator = FRotator(183.39f, -3.389973f, 218.382874f);

	// Create a Quaternion from a Rotator
	FQuat QuatRightCollision = FQuat(RightCollisionRotator);

	// Set Rotation
	fTransform.SetRotation(QuatRightCollision);

	// Set Right Foot transform on Right Foot Character
	FootCollision->SetWorldTransform(fTransform);
}

void AAsaiMakiFootCollision::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

