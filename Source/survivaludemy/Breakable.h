// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "survivaludemy/Interface/HitInterface.h"
#include "Breakable.generated.h"

UCLASS()
class SURVIVALUDEMY_API ABreakable : public AActor, public IHitInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

	UPROPERTY(VisibleAnywhere)
	class UGeometryCollectionComponent* GeometryCollectionComponent;
};
