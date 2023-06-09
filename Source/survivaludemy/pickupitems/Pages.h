// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pages.generated.h"

UCLASS()
class SURVIVALUDEMY_API APages : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APages();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	class AIgnoreActor* IgnoreActorCpp;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int indexCpp;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere)
	//bool OverlappedCpp;

	UFUNCTION(BlueprintCallable)
	void Starting();
};
