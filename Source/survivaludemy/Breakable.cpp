// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakable.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
// Sets default values
ABreakable::ABreakable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GeometryCollectionComponent = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("Component"));
	SetRootComponent(GeometryCollectionComponent);
}

// Called when the game starts or when spawned
void ABreakable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakable::GetHit_Implementation(const FVector& ImpactPoint)
{
}

