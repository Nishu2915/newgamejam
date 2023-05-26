// Fill out your copyright notice in the Description page of Project Settings.


#include "IgnoreActor.h"
#include "Kismet/GameplayStatics.h"
#include "A_SaveGame.h"
#include "survivaludemyCharacter.h"
#include "Pickupitems/Pages.h"
// Sets default values
AIgnoreActor::AIgnoreActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NoOfPagesCollectedCpp = 0;
	NoOfWinOnDragonCpp = 0;
	//WhichPagesCollected.Init(-1, 5);
}

// Called when the game starts or when spawned
void AIgnoreActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIgnoreActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIgnoreActor::SaveGameToSlot()
{
	SaveGameptr = Cast<UA_SaveGame>(UGameplayStatics::LoadGameFromSlot(FString("data"), 0));
	if (!SaveGameptr) {
		SaveGameptr = Cast<UA_SaveGame>(UGameplayStatics::CreateSaveGameObject(UA_SaveGame::StaticClass()));
	}
	SaveGameptr->NoOfPagesSave = NoOfPagesCollectedCpp;
	SaveGameptr->NoOfDragonSave = NoOfWinOnDragonCpp;
	SaveGameptr->CollectedPagesSave = WhichPagesCollected;
	UGameplayStatics::SaveGameToSlot(SaveGameptr,FString("data"),0);
}

void AIgnoreActor::ResumeFunc()
{
	SaveGameptr = Cast<UA_SaveGame>(UGameplayStatics::LoadGameFromSlot(FString("data"), 0));
	if (SaveGameptr) {
		NoOfWinOnDragonCpp = SaveGameptr->NoOfDragonSave ;
		NoOfPagesCollectedCpp = SaveGameptr->NoOfPagesSave;
		CurrentIndex = SaveGameptr->CurrentIndexSave;
		if (SaveGameptr->NoOfDragonSave = SaveGameptr->NoOfPagesSave) {
			AsurvivaludemyCharacter* Character =  Cast<AsurvivaludemyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (Character) {
				Character->SetActorLocation(CppActor[CurrentIndex]->GetActorLocation());
			}
			for (int i = 0; i < SaveGameptr->NoOfPagesSave; i++) {
				CppActor[WhichPagesCollected[i]]->SetActorHiddenInGame(false);
				CppActor[WhichPagesCollected[i]]->SetActorEnableCollision(false);
				CppActor[WhichPagesCollected[i]]->SetActorTickEnabled(false);
			}
		}
		else {
			// case start fight of attack on CurrentIndex
		}
	}
}

