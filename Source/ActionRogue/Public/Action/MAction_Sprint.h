// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MAction.h"
#include "MAction_Sprint.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUE_API UMAction_Sprint : public UMAction
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditDefaultsOnly,Category="Sprint")
	float AddSpeed;

public:
	UMAction_Sprint();

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;
};
