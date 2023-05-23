// Fill out your copyright notice in the Description page of Project Settings.


#include "Parent_item.h"
#include "Components/SphereComponent.h"

// Sets default values
AParent_item::AParent_item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OverlappingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
	SetRootComponent(Mesh);
	OverlappingSphere->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AParent_item::BeginPlay()
{
	Super::BeginPlay();
	OverlappingSphere->OnComponentBeginOverlap.AddDynamic(this, &AParent_item::OnOverlapBegin);
	OverlappingSphere->OnComponentEndOverlap.AddDynamic(this, &AParent_item::OnOverlapEnd);
}

// Called every frame
void AParent_item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParent_item::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GEngine) {
		//GEngine->AddOnScreenDebugMessage(0, 5, FColor::Black, FString("ParentEndoverlap"));
	}
}

void AParent_item::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine) {
		//GEngine->AddOnScreenDebugMessage(0, 5, FColor::Black, FString("Parentoverlap"));
	}
}

