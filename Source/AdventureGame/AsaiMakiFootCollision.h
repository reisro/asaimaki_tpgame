// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "AsaiMakiFootCollision.generated.h"

UCLASS()
class ADVENTUREGAME_API AAsaiMakiFootCollision : public AActor
{
	GENERATED_BODY()

	/** Right Foot Socket to simulate collision against right foot character animations */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sockets Collision", meta = (AllowPrivateAccess = "true"))
	UBoxComponent * FootCollision;
	
public:	
	// Sets default values for this actor's properties
	AAsaiMakiFootCollision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// declare overlap begin function
	UFUNCTION()
		void CreateFootCollision(const char * collisionName);

	// declare overlap begin function
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
