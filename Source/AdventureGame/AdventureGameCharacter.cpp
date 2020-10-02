// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AdventureGameCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "FootCollisionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CheatManager.h"
#include "Engine/EngineTypes.h"

//////////////////////////////////////////////////////////////////////////
// AAdventureGameCharacter

AAdventureGameCharacter::AAdventureGameCharacter():
	Health(100), NinjaLevel(1)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	NinjaAttributeSet = CreateDefaultSubobject<UNinjaAttributeSet>(TEXT("NinjaAttributeSet"));
	NinjaAbilitySystem = CreateDefaultSubobject<UNinjaAbilitySystemComponent>(TEXT("NinjaAbilitySystemComponent"));
	
	//CheatClass = UCheatManager::StaticClass();

	// Set collision sockets
	LeftFootSocket = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftFootColl"));
	RightFootSocket = CreateDefaultSubobject<UBoxComponent>(TEXT("RightFootCol"));

	// Create rules for attaching sockets on components
	FAttachmentTransformRules transformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);

	LeftFootSocket->AttachToComponent(GetMesh(), transformRules, FName(TEXT("LeftFoot")));
	RightFootSocket->AttachToComponent(GetMesh(), transformRules, FName(TEXT("RightFoot")));

	// Create a transform that holds location, rotation and scale of collision components
	FTransform fTransform;
	FTransform RFTransform;

	// Set Location
	fTransform.SetLocation(FVector(0.067608f, 6.154139f, 6.77425f));
	RFTransform.SetLocation(FVector(-25.076216f, 6.154139f, 6.77425f));
	
	// Set Rotator with float values
	FRotator LeftCollisionRotator = FRotator(-89.148125f, 89.399956f, 0.024115f);
	FRotator RightCollisionRotator = FRotator(-89.148125f, 89.399956f, 0.024115f);

	// Create a Quaternion from a Rotator
	FQuat QuatLeftCollision = FQuat(LeftCollisionRotator);
	FQuat QuatRightCollision = FQuat(RightCollisionRotator);

	// Set Rotation
	fTransform.SetRotation(QuatLeftCollision);
	RFTransform.SetRotation(QuatRightCollision);

	// Set Scale
	fTransform.SetScale3D(FVector(0.4385f, 0.1727f, 0.1464f));
	RFTransform.SetScale3D(FVector(0.4385f, 0.1727f, 0.1464f)); 

	LeftFootSocket->SetRelativeTransform(fTransform);
	LeftFootSocket->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LeftFootSocket->SetGenerateOverlapEvents(true);
	LeftFootSocket->SetCollisionProfileName(TEXT("BlockAll"));

	RightFootSocket->SetRelativeTransform(fTransform);
	RightFootSocket->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RightFootSocket->SetGenerateOverlapEvents(true);
	RightFootSocket->SetCollisionProfileName(TEXT("BlockAll"));

	// add a dynamic delegate when this collision is overlapped
	RightFootSocket->OnComponentBeginOverlap.AddDynamic(this, &AAdventureGameCharacter::BeginOverlap);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AAdventureGameCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Initialize our abilities
	if (NinjaAbilitySystem)
	{
		NinjaAbilitySystem->InitAbilityActorInfo(this, this);
		ActivateStartupNinjaAbility();
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAdventureGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAdventureGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAdventureGameCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AAdventureGameCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AAdventureGameCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AAdventureGameCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AAdventureGameCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AAdventureGameCharacter::OnResetVR);
}

int32 AAdventureGameCharacter::GetHealth() const
{
	UE_LOG(LogTemp, Warning, TEXT("Character Health %d"), this->Health);

	return this->Health;
	//return NinjaAttributeSet->GetHealth();
}

void AAdventureGameCharacter::SetHealth(int32 _health)
{
	Health = _health;
}

void AAdventureGameCharacter::ActivateStartupNinjaAbility()
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
}

void AAdventureGameCharacter::GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags,
	TArray<UNinjaGameplayAbility*>& ActiveAbilities)
{
	if (NinjaAbilitySystem)
		NinjaAbilitySystem->GetActiveAbilitiesWithTags(AbilityTags, ActiveAbilities);
}

bool AAdventureGameCharacter::ActivateAbilitiesWithTag(FGameplayTagContainer AbilityTag, bool bAllowRemoteActivation)
{
	if (NinjaAbilitySystem)
		return NinjaAbilitySystem->TryActivateAbilitiesByTag(AbilityTag, bAllowRemoteActivation);

	return false;
}

int AAdventureGameCharacter::GetGameplayAbilities() const
{
	return GameplayAbilities.Num();
}

FString AAdventureGameCharacter::GetGameplayAbilityName() const
{
	FString none = "";
	
	for (auto const abilityName: GameplayAbilities)
	{
		return abilityName.GetDefaultObject()->AbilityTags.ToString();
	}

	return none;
}

UAbilitySystemComponent* AAdventureGameCharacter::GetAbilitySystemComponent() const
{
	return NinjaAbilitySystem;
}

void AAdventureGameCharacter::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (this->ActorHasTag(TEXT("Player")))) 
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());

		// hold a reference for the hit character
		AAdventureGameCharacter * character = Cast<AAdventureGameCharacter>(OtherActor);

		character->SetHealth(0);

		// get anim instance from hit character
		NinjaAnimInstance = Cast<UAsaiMakiAnimInstance>(character->GetMesh()->GetAnimInstance());

		// get anim instance from this character
		UAsaiMakiAnimInstance* PlayerAnimInstance;
		PlayerAnimInstance = Cast<UAsaiMakiAnimInstance>(this->GetMesh()->GetAnimInstance());

		if (AsaiMakiAnimInstance == nullptr)
			UE_LOG(LogTemp, Warning, TEXT("Some warning message"));

		//FDetachmentTransformRules transformRules = FDetachmentTransformRules(EDetachmentRule::KeepWorld);

		//character->GetMesh()->DetachFromComponent(transformRules);
		//CameraBoom->DetachFromParent(true);

		// avoid collision with capsule component, skeletal mesh
		// and left and right socket collisions
		character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
		character->GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
		character->LeftFootSocket->SetCollisionProfileName(TEXT("NoCollision"));
		character->RightFootSocket->SetCollisionProfileName(TEXT("NoCollision"));

		UE_LOG(LogTemp, Warning, TEXT("%s Kicking %s"), *this->GetName(), PlayerAnimInstance->EnableKick?TEXT("true"):TEXT("false"));

		// triggers hit animation if player is kicking 
		if (PlayerAnimInstance->EnableKick)
		{
			// triggers ninja character screw animation
			NinjaAnimInstance->Hit = true;
			// activates slow motion effect in game speed
			//CheatManager->Slomo(Slowmotion);
		}
	}
}

void AAdventureGameCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AAdventureGameCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AAdventureGameCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AAdventureGameCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AAdventureGameCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AAdventureGameCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AAdventureGameCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}