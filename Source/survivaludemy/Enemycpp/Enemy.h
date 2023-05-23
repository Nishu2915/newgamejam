// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "survivaludemy/Interface/HitInterface.h"
#include "Enemy.generated.h"

UCLASS()
class SURVIVALUDEMY_API AEnemy : public ACharacter , public IHitInterface
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	virtual void BeginPlay() override;
public:	
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

	void HitMontageFunc(const FVector& ImpactPoint);
	
    

	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* HitMontage;
};
