// Copyright Epic Games, Inc. All Rights Reserved.

#include "survivaludemyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimMontage.h"
#include "pickupitems/Hammer.h"
#include "Components/BoxComponent.h"


//////////////////////////////////////////////////////////////////////////
// AsurvivaludemyCharacter

AsurvivaludemyCharacter::AsurvivaludemyCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AsurvivaludemyCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AsurvivaludemyCharacter::Attack()
{
	if (AttackingState == EAttackingState::ECS_NotAttacking && CharState==ECharState::ECS_EquippedHammer) {
		AttackingState = EAttackingState::ECS_Attacking;
		HammerAttack();
	}
}

void AsurvivaludemyCharacter::HammerAttack()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage) {
		AnimInstance->Montage_Play(AttackMontage, 2.0f);
		bool Selection = FMath::RandBool();
		if (Selection) {
			AnimInstance->Montage_JumpToSection(FName("Attack1"), AttackMontage);
		}
		else {
			AnimInstance->Montage_JumpToSection(FName("Attack2"), AttackMontage);
		}
	}
}

void AsurvivaludemyCharacter::EquipFromBack()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (CharState == ECharState::ECS_unequipped) return;
	if (AnimInstance && EquipMontage) {
		AnimInstance->Montage_Play(EquipMontage);
		if (CharState == ECharState::ECS_EquippedHammer) {
			AnimInstance->Montage_JumpToSection(FName("UnEquip"), EquipMontage);
			CharState = ECharState::ECS_HammerAtBack;
		}
		else if (CharState == ECharState::ECS_HammerAtBack) {
			AnimInstance->Montage_JumpToSection(FName("Equip"), EquipMontage);
			CharState = ECharState::ECS_EquippedHammer;
		}
	}
}

void AsurvivaludemyCharacter::AttackEnd()
{
	AttackingState = EAttackingState::ECS_NotAttacking; 
}

void AsurvivaludemyCharacter::setOverlappingActor(AHammer* Hammer)
{
	OverlappedHammer = Hammer;
}

void AsurvivaludemyCharacter::AttachToBack()
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	OverlappedHammer->Mesh->AttachToComponent(GetMesh(), TransformRules, FName("BackSocket"));
}

void AsurvivaludemyCharacter::AttachToHand()
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	OverlappedHammer->Mesh->AttachToComponent(GetMesh(), TransformRules, FName("ItemSocket"));
}

void AsurvivaludemyCharacter::SetCollisionOfWeapon(ECollisionEnabled::Type CollisionEnabled)
{
	if(OverlappedHammer && OverlappedHammer->GetWeaponBox())
	OverlappedHammer->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
	OverlappedHammer->IgnoreActors.Empty();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AsurvivaludemyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AsurvivaludemyCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AsurvivaludemyCharacter::Look);
		InputComponent->BindAction(FName("Attack"), IE_Pressed, this, &AsurvivaludemyCharacter::Attack);
		InputComponent->BindAction(FName("Equip"), IE_Pressed, this, &AsurvivaludemyCharacter::EquipFromBack);
	}

}

void AsurvivaludemyCharacter::Move(const FInputActionValue& Value)
{
	if (AttackingState == EAttackingState::ECS_Attacking) return;
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AsurvivaludemyCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}




