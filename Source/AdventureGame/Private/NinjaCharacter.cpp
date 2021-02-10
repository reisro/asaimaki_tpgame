// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaCharacter.h"

// Sets default values
ANinjaCharacter::ANinjaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ANinjaCharacter::PossessedBy(AController* NewController)
{
}

// Called when the game starts or when spawned
void ANinjaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANinjaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANinjaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int32 ANinjaCharacter::GetHealth() const
{
	return 0;
}

void ANinjaCharacter::SetHealth(int32 _health)
{
}

void ANinjaCharacter::ActivateStartupNinjaAbility()
{
}

void ANinjaCharacter::GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags,
	TArray<UNinjaGameplayAbility*>& ActiveAbilities)
{
}

bool ANinjaCharacter::ActivateAbilitiesWithTag(FGameplayTagContainer AbilityTag, bool bAllowRemoteActivation)
{
	return true;
}

int ANinjaCharacter::GetGameplayAbilities() const
{
	return 0;
}

UAbilitySystemComponent* ANinjaCharacter::GetAbilitySystemComponent() const
{
	return NinjaAbilitySystem;
}

void ANinjaCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ANinjaCharacter::OnHealthDamage(float DeltaValue, const FGameplayTagContainer& EventTags)
{
}

void ANinjaCharacter::OnHitDamage(float DamageAmount, const FHitResult& HitInfo,
	const FGameplayTagContainer& DamageTags, ANinjaCharacter* InstigatorCharacter, AActor* DamageCauser)
{
}

