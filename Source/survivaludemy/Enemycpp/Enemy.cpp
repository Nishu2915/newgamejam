// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy::GetHit_Implementation(const FVector& ImpactPoint)
{
	HitMontageFunc(ImpactPoint);
}

void AEnemy::HitMontageFunc(const FVector& ImpactPoint)
{
	FVector Forward = GetActorForwardVector();
	FVector LowerImpact(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	FVector BVector = (LowerImpact - GetActorLocation()).GetSafeNormal();
	double dot = FVector::DotProduct(Forward, BVector);
	double rad = FMath::Acos(dot);
	double theta = FMath::RadiansToDegrees(rad);
	FVector crss = FVector::CrossProduct(Forward, BVector);
	if (crss.Z <= 0) {
		theta = theta * -1.0f;
	}
	FName Section("HitBack");
	if (theta >= -45.f && theta < 45.f) Section = FName("HitFront");
	else if (theta >= -135.f && theta < -45.f) Section = FName("HitLeft");
	else if (theta >= 45.f && theta < 135.f) Section = FName("HitRight");

	UAnimInstance* EnemyAnimInstance = GetMesh()->GetAnimInstance();
	if (EnemyAnimInstance && HitMontage) {
		EnemyAnimInstance->Montage_Play(HitMontage);
		EnemyAnimInstance->Montage_JumpToSection(Section, HitMontage);
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

