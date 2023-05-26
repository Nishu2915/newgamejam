// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "A_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALUDEMY_API UA_SaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	int NoOfPagesSave;
	int NoOfDragonSave;
	TArray<int> CollectedPagesSave;
};
