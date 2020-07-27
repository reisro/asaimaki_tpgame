// Fill out your copyright notice in the Description page of Project Settings.


#include "FootCollisionComponent.h"

// Sets default values for this component's properties
UFootCollisionComponent::UFootCollisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UFootCollisionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UFootCollisionComponent::CreateFootCollision(USceneComponent * parent)
{
	// Set collision sockets
	FootCollision = CreateDefaultSubobject<UBoxComponent>("CollisionComp");

	// Create rules for attaching sockets on components
	FAttachmentTransformRules transformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);

	FootCollision->AttachToComponent(parent, transformRules, FName(TEXT("RightFoot")));

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


// Called every frame
void UFootCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}