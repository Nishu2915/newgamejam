// Fill out your copyright notice in the Description page of Project Settings.


#include "A_animinstance.h"
#include "survivaludemy/survivaludemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UA_animinstance::UpdateAnimationProperties(float DeltaTime)
{
	if (RealChar == nullptr) {
		RealChar = Cast<AsurvivaludemyCharacter>(TryGetPawnOwner());
	}
	if (RealChar) {
		FVector Forward = RealChar->GetActorForwardVector();
		FVector Velocity = RealChar->GetVelocity();
		Velocity.Z = 0;
		speed = FVector::DotProduct(Forward, Velocity);
		BIsInAir = RealChar->GetCharacterMovement()->IsFalling();
		CharState = RealChar->CharState;
		//FVector Velocity = RealChar->GetVelocity();
		//Velocity.Z = 0;
		//speed = Velocity.Size();
	}
}

void UA_animinstance::NativeInitializeAnimation()
{
	RealChar =  Cast<AsurvivaludemyCharacter>(TryGetPawnOwner());
}
