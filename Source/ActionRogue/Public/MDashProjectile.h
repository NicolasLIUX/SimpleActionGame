// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "MDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUE_API AMDashProjectile : public AProjectileBase
{
	GENERATED_BODY()
protected:
	
	UPROPERTY(EditDefaultsOnly,Category="Teleport")
	float TeleportDelay;

	UPROPERTY(EditDefaultsOnly,Category="Teleport")
	float DetonateDelay;

	FTimerHandle TimerHandle_DetoanteDelay;

	virtual void Explode_Implementation() override;

	void TeleportInstigatytor();

	virtual void BeginPlay() override;
	
public:
	AMDashProjectile();
};
