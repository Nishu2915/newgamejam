// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parent_item.h"
#include "Hammer.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALUDEMY_API AHammer : public AParent_item
{
	GENERATED_BODY()
public:
		AHammer();
		//virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
        
		UFUNCTION()
		void OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		bool once = true;

		UPROPERTY(VisibleAnywhere)
		class UBoxComponent* BoxComponent;
		
		UPROPERTY(VisibleAnywhere)
		USceneComponent* StartLoc;

		UPROPERTY(VisibleAnywhere)
		USceneComponent* EndLoc;

		UBoxComponent* GetWeaponBox();
		
		TArray<AActor*> IgnoreActors;

		UFUNCTION(BlueprintImplementableEvent)
		void CreateFields(const FVector& FieldLocation);
protected:
	virtual void BeginPlay() ;
};
