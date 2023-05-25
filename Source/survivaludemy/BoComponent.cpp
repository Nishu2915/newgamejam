// Fill out your copyright notice in the Description page of Project Settings.


#include "BoComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
// Sets default values for this component's properties
UBoComponent::UBoComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBox"));
	StartLoc = CreateDefaultSubobject<USceneComponent>(TEXT("StartLoc"));
	EndLoc = CreateDefaultSubobject<USceneComponent>(TEXT("EndLoc"));
	// ...
}


// Called when the game starts
void UBoComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBoComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

