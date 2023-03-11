// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ProjectileBase.h"
#include "Action/MAction_Effect.h"
#include "MPrimaryProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUE_API AMPrimaryProjectile : public AProjectileBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Damage")
	float DamageValue;

	UPROPERTY(EditDefaultsOnly,Category="Damage")
	FGameplayTag ParryTag;

	UPROPERTY(EditDefaultsOnly,Category="Damage")
	TSubclassOf<UMAction_Effect> BurningActionClass;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	AMPrimaryProjectile();

	
};
