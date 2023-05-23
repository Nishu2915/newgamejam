// Fill out your copyright notice in the Description page of Project Settings.


#include "Hammer.h"
#include "survivaludemy/survivaludemyCharacter.h"
#include "survivaludemy/UserCreatedEnum.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Interface/HitInterface.h"

//void AHammer::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
	//Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
//}

AHammer::AHammer()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBox"));
	StartLoc = CreateDefaultSubobject<USceneComponent>(TEXT("StartLoc"));
	EndLoc = CreateDefaultSubobject<USceneComponent>(TEXT("EndLoc"));
	BoxComponent->SetupAttachment(Mesh);
	StartLoc->SetupAttachment(Mesh);
	EndLoc->SetupAttachment(Mesh);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}



UBoxComponent* AHammer::GetWeaponBox()
{
	return BoxComponent;
}

void AHammer::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AHammer::OnWeaponOverlap);
	
}

void AHammer::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	AsurvivaludemyCharacter* RealChar = Cast<AsurvivaludemyCharacter>(OtherActor);
	if (RealChar && once) {
		once = false;
		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget,true);
		Mesh->AttachToComponent(RealChar->GetMesh(), TransformRules, FName("ItemSocket"));
		RealChar->CharState = ECharState::ECS_EquippedHammer;
		RealChar->setOverlappingActor(this);
		//if (GEngine) {
			//GEngine->AddOnScreenDebugMessage(0, 5, FColor::Black, FString("Childoverlap"));
		//}
	}
	
}

void AHammer::OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AsurvivaludemyCharacter* RealChar = Cast<AsurvivaludemyCharacter>(OtherActor);
	
	TArray<AActor*> ActorToIgnore;
	if (RealChar) ActorToIgnore.Add(RealChar);
	ActorToIgnore.Add(this);
	for (AActor* Actor : IgnoreActors) {
		ActorToIgnore.AddUnique(Actor);
	}
	FVector Start = StartLoc->GetComponentLocation();
	FVector End =  EndLoc->GetComponentLocation();
	FHitResult HitResult;
	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		FVector(5.0f, 5.0f, 5.0f),
		StartLoc->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorToIgnore,
		EDrawDebugTrace::None,
		HitResult,
		true
	);
	if (HitResult.GetActor()) {
		IHitInterface* HitInterface = Cast<IHitInterface>(HitResult.GetActor());
		if (HitInterface) {
			//HitInterface->GetHit(HitResult.ImpactPoint);
			HitInterface->Execute_GetHit(HitResult.GetActor(), HitResult.ImpactPoint);
		}
		IgnoreActors.AddUnique(HitResult.GetActor());
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString("impact"));
		}
		CreateFields(HitResult.ImpactPoint);
	}
}

