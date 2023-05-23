// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "UserCreatedEnum.h"
#include "survivaludemyCharacter.generated.h"


UCLASS(config=Game)
class AsurvivaludemyCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	AsurvivaludemyCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	ECharState CharState = ECharState::ECS_unequipped;

	void Attack();
	void HammerAttack();
	void EquipFromBack();
	
	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	EAttackingState AttackingState = EAttackingState::ECS_NotAttacking;

	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* EquipMontage;

	class AHammer* OverlappedHammer;

	void setOverlappingActor(AHammer* Hammer);

	UFUNCTION(BlueprintCallable)
	void AttachToBack();

	UFUNCTION(BlueprintCallable)
	void AttachToHand();

	UFUNCTION(BlueprintCallable)
	void SetCollisionOfWeapon(ECollisionEnabled::Type CollisionEnabled);
};

