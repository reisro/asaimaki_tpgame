// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaCharacter.h"

// Sets default values
ANinjaCharacter::ANinjaCharacter():
Health(100), NinjaLevel(1)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	NinjaAttributeSet = CreateDefaultSubobject<UNinjaAttributeSet>(TEXT("NinjaAttributeSet"));
	NinjaAbilitySystem = CreateDefaultSubobject<UNinjaAbilitySystemComponent>(TEXT("NinjaAbilitySystemComponent"));

	// Set collision sockets
	LeftFootCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftFootColl"));
	RightFootCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("RightFootCol"));

	// Create rules for attaching sockets on components
	FAttachmentTransformRules transformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);

	LeftFootCollider->SetupAttachment(GetMesh(), FName(TEXT("LeftFoot")));
	RightFootCollider->SetupAttachment(GetMesh(), FName(TEXT("RightFoot")));

	// Create a transform that holds location, rotation and scale of collision components
	FTransform LFTransform;
	FTransform RFTransform;

	// Set Location
	LFTransform.SetLocation(FVector(0.067608f, 6.154139f, 6.77425f));
	RFTransform.SetLocation(FVector(-25.076216f, 6.154139f, 6.77425f));

	// Set Rotator with float values
	FRotator LeftCollisionRotator = FRotator(-89.148125f, 89.399956f, 0.024115f);
	FRotator RightCollisionRotator = FRotator(-89.148125f, 89.399956f, 0.024115f);

	// Create a Quaternion from a Rotator
	FQuat QuatLeftCollision = FQuat(LeftCollisionRotator);
	FQuat QuatRightCollision = FQuat(RightCollisionRotator);

	// Set Rotation
	LFTransform.SetRotation(QuatLeftCollision);
	RFTransform.SetRotation(QuatRightCollision);

	// Set Scale
	LFTransform.SetScale3D(FVector(0.4385f, 0.1727f, 0.1464f));
	RFTransform.SetScale3D(FVector(0.4385f, 0.1727f, 0.1464f));

	LeftFootCollider->SetRelativeTransform(LFTransform);
	LeftFootCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LeftFootCollider->SetGenerateOverlapEvents(true);
	LeftFootCollider->SetCollisionProfileName(TEXT("BlockAll"));

	RightFootCollider->SetRelativeTransform(RFTransform);
	RightFootCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RightFootCollider->SetGenerateOverlapEvents(true);
	RightFootCollider->SetCollisionProfileName(TEXT("BlockAll"));

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
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

// Called every frame
void ANinjaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANinjaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

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

