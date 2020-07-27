// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "FootCollisionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADVENTUREGAME_API UFootCollisionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UFootCollisionComponent();

	/** Right Foot Socket to simulate collision against right foot character animations */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sockets Collision", meta = (AllowPrivateAccess = "true"))
		UBoxComponent * FootCollision;

	UFUNCTION()
	void CreateFootCollision(USceneComponent * parent);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
