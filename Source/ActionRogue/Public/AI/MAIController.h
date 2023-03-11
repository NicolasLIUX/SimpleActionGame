// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MAIController.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUE_API AMAIController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,Category="AI")
	UBehaviorTree* BehaviorTree;

	virtual void BeginPlay() override;
};
