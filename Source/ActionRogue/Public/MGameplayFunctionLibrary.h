// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MGameplayFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUE_API UMGameplayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,Category="GamePlay")
	static bool ApplyDamage(AActor* DamageCasuser,AActor* TargetActor,float DamgeAmount);

	UFUNCTION(BlueprintCallable,Category="GamePlay")
	static bool ApplyDirectionalDamage(AActor* DamageCasuser,AActor* TargetActor,float DamgeAmount,const FHitResult& HitResult);
};
