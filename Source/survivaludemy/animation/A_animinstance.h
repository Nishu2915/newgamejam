// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "survivaludemy/UserCreatedEnum.h"
#include "A_animinstance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALUDEMY_API UA_animinstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

	virtual void NativeInitializeAnimation() override; 

	UPROPERTY(BlueprintReadOnly)
	class AsurvivaludemyCharacter* RealChar;

public:
	UPROPERTY(BlueprintReadOnly)
	float speed = 0;

	UPROPERTY(BlueprintReadOnly)
	bool BIsInAir;

	UPROPERTY(BlueprintReadOnly)
	ECharState CharState;
};
