// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MAction.h"
#include "MAction_Effect.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUE_API UMAction_Effect : public UMAction
{
	GENERATED_BODY()
public:

	UMAction_Effect();
	
	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Effect")
	float Duration;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Effect")
	float Period;

	FTimerHandle TimerHandle_Duration;
	FTimerHandle TimerHandle_Period;

	UFUNCTION(BlueprintNativeEvent,Category="Effect")
	void ExecutePeriodEffect(AActor* Instigator);

	UFUNCTION(BlueprintCallable,Category="Action")
	float GetTimeRemaining() const;
};
