// Fill out your copyright notice in the Description page of Project Settings.


#include "AsaiMakiNinja.h"

AAsaiMakiNinja::AAsaiMakiNinja():ANinjaCharacter()
{
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
}

void AAsaiMakiNinja::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if ((OtherActor != nullptr) && (OtherActor != this) && (this->ActorHasTag(TEXT("Enemy"))))
        UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());
}

void AAsaiMakiNinja::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // Set up gameplay key bindings
    check(PlayerInputComponent);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    
    PlayerInputComponent->BindAxis("MoveForward", this, &AAsaiMakiNinja::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AAsaiMakiNinja::MoveRight);

    // We have 2 versions of the rotation bindings to handle different kinds of devices differently
    // "turn" handles devices that provide an absolute delta, such as a mouse.
    // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &AAsaiMakiNinja::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookUpRate", this, &AAsaiMakiNinja::LookUpAtRate);
}

void AAsaiMakiNinja::SetupBodyCollidersName()
{
    LeftHandBoneName = FName(TEXT("LeftHand"));
	RightHandBoneName = FName(TEXT("RightHand"));
	LeftFootBoneName = FName(TEXT("LeftFoot"));
	RightFootBoneName = FName(TEXT("RightFoot"));
}

void AAsaiMakiNinja::MoveForward(float Value)
{
    if ((Controller != NULL) && (Value != 0.0f))
    	{
    		// find out which way is forward
    		const FRotator Rotation = Controller->GetControlRotation();
    		const FRotator YawRotation(0, Rotation.Yaw, 0);
    
    		// get forward vector
    		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        
            if (EnablePlayerInput)
    		    AddMovementInput(Direction, Value);
    	}
}

void AAsaiMakiNinja::MoveRight(float Value)
{
    if ( (Controller != NULL) && (Value != 0.0f))
    {
        // find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
	
        // get right vector 
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        // add movement in that direction

        if (EnablePlayerInput)
            AddMovementInput(Direction, Value);
    }
}

void AAsaiMakiNinja::TurnAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AAsaiMakiNinja::LookUpAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AAsaiMakiNinja::CheckIfAnyMontageIsBeingPlayed()
{
    return EnablePlayerInput;
}

void AAsaiMakiNinja::BeginPlay()
{
    // Get the Anim Instance attached to this character
    AsaiMakiAnimInstance = Cast<UAsaiMakiAnimInstance>(this->GetMesh()->GetAnimInstance());

    UE_LOG(LogTemp, Warning, TEXT("%s"), *this->GetMesh()->GetAnimInstance()->GetName());
    UE_LOG(LogTemp, Warning, TEXT("Hello"));
}

// Called every frame
void AAsaiMakiNinja::LogInParentTick(float DeltaTime)
{
    UE_LOG(LogTemp, Warning, TEXT("aaaaaaaaaaaaaaa."));
    
    if (AsaiMakiAnimInstance != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Not null."));
        
        if (!AsaiMakiAnimInstance->IsAnyMontagePlaying())
        {
            UE_LOG(LogTemp, Warning, TEXT("Input enabled."));

            EnablePlayerInput=true;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Input disabled."));

            EnablePlayerInput=false;
        }
    }
    else
        UE_LOG(LogTemp, Warning, TEXT("Anim null."));
}
