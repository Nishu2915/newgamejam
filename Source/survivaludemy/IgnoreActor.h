// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IgnoreActor.generated.h"

UCLASS()
class SURVIVALUDEMY_API AIgnoreActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIgnoreActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<class APages*> CppActor;

	UPROPERTY(BlueprintReadWrite)
	int NoOfPagesCollectedCpp;
	
	UPROPERTY(BlueprintReadWrite)
	int	NoOfWinOnDragonCpp;
		
	UPROPERTY(BlueprintReadWrite)
	int CurrentIndex;

	UPROPERTY(BlueprintReadWrite)
	TArray<int> WhichPagesCollected;

	void SaveGameToSlot();

	class UA_SaveGame* SaveGameptr;

	UFUNCTION(BlueprintCallable)
	void ResumeFunc();
};
