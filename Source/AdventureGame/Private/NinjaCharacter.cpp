// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaCharacter.h"

// Sets default values
ANinjaCharacter::ANinjaCharacter():
Health(100), NinjaLevel(1)
{
	UE_LOG(LogTemp, Warning, TEXT("Ninja Character Constructor"));

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	NinjaAttributeSet = CreateDefaultSubobject<UNinjaAttributeSet>(TEXT("NinjaAttributeSet"));
	NinjaAbilitySystem = CreateDefaultSubobject<UNinjaAbilitySystemComponent>(TEXT("NinjaAbilitySystemComponent"));
	
	SetupBodyCollidersName();
}

void ANinjaCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Initialize our abilities
	if (NinjaAbilitySystem)
	{
		NinjaAbilitySystem->InitAbilityActorInfo(this, this);
		ActivateStartupNinjaAbility();
	}
}

// Called when the game starts or when spawned
void ANinjaCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

void ANinjaCharacter::SetupBodyCollidersName()
{
	// Set collision sockets
	//LeftHandCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftHandCol"));
	//RightHandCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHandCol"));
	//LeftFootCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftFootCol"));
	//RightFootCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("RightFootCol"));

	//LeftHandCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//LeftHandCollider->SetGenerateOverlapEvents(true);
	//LeftHandCollider->SetCollisionProfileName(TEXT("BlockAll"));
	
	//RightHandCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//RightHandCollider->SetGenerateOverlapEvents(true);
	//RightHandCollider->SetCollisionProfileName(TEXT("BlockAll"));
	
	//LeftFootCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//LeftFootCollider->SetGenerateOverlapEvents(true);
	//LeftFootCollider->SetCollisionProfileName(TEXT("BlockAll"));

	//RightFootCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//RightFootCollider->SetGenerateOverlapEvents(true);
	//RightFootCollider->SetCollisionProfileName(TEXT("BlockAll"));
}

// Called every frame
void ANinjaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ANinjaCharacter::GetHealth() const
{
	UE_LOG(LogTemp, Warning, TEXT("Character Health %d"), this->Health);

	return this->Health;
}

void ANinjaCharacter::SetHealth(int32 _health)
{
	Health = _health;
}

void ANinjaCharacter::ActivateStartupNinjaAbility()
{
	check(NinjaAbilitySystem);

	if (GetLocalRole() == ROLE_Authority && !bAbilitesInitialized)
	{
		for (TSubclassOf<UNinjaGameplayAbility>& StartupAbility: GameplayAbilities)
		{
			NinjaAbilitySystem->GiveAbility(FGameplayAbilitySpec(StartupAbility, NinjaLevel, INDEX_NONE, this));
			UE_LOG(LogTemp, Warning, TEXT("Added startup gameplay abilities to %s"), *this->GetName() );
		}
	}

	// Now apply passives
	for (TSubclassOf<UGameplayEffect>& GameplayEffect : PassiveGameplayEffects)
	{
		FGameplayEffectContextHandle EffectContext = NinjaAbilitySystem->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = NinjaAbilitySystem->MakeOutgoingSpec(GameplayEffect, NinjaLevel, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = NinjaAbilitySystem->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), NinjaAbilitySystem);
		}
	}
}

void ANinjaCharacter::GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags,
	TArray<UNinjaGameplayAbility*>& ActiveAbilities)
{
	if (NinjaAbilitySystem)
		NinjaAbilitySystem->GetActiveAbilitiesWithTags(AbilityTags, ActiveAbilities);
}

bool ANinjaCharacter::ActivateAbilitiesWithTag(FGameplayTagContainer AbilityTag, bool bAllowRemoteActivation)
{
	if (NinjaAbilitySystem)
		return NinjaAbilitySystem->TryActivateAbilitiesByTag(AbilityTag, bAllowRemoteActivation);

	return false;
}

int ANinjaCharacter::GetGameplayAbilities() const
{
	return GameplayAbilities.Num();
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
	OnDamaged(DamageAmount, HitInfo, DamageTags, InstigatorCharacter, DamageCauser);
}