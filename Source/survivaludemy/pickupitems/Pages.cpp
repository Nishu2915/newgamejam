// Fill out your copyright notice in the Description page of Project Settings.


#include "Pages.h"
#include "..\IgnoreActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APages::APages()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APages::BeginPlay()
{
	Super::BeginPlay();
	TSubclassOf<AActor> ActorClass = AIgnoreActor::StaticClass();
	TArray<AActor*> OutActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ActorClass ,OutActor);
	IgnoreActorCpp = Cast<AIgnoreActor>(OutActor[0]);
	
}

// Called every frame
void APages::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APages::Starting()
{

	//IgnoreActorCpp->CppActor[indexCpp]->OverlappedCpp = true;
	IgnoreActorCpp->CurrentIndex = indexCpp;
	//IgnoreActorCpp->WhichPagesCollected[IgnoreActorCpp->NoOfPagesCollectedCpp] = indexCpp;
	IgnoreActorCpp->WhichPagesCollected.AddUnique(indexCpp);
	IgnoreActorCpp->NoOfPagesCollectedCpp = +1;
	switch (indexCpp) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	}
}

