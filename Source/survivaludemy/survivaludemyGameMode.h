// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "survivaludemyGameMode.generated.h"

UCLASS(minimalapi)
class AsurvivaludemyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AsurvivaludemyGameMode();



	UPROPERTY(BlueprintReadWrite)
	int NumberOfPagesCollect;
};



