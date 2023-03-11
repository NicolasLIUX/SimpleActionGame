// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MAction.h"
#include "MAction_ProjectileAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUE_API UMAction_ProjectileAttack : public UMAction
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly,Category="Effect")
	FName HandSocketName;

	UPROPERTY(EditDefaultsOnly,Category="Attack")
	float AttackAnimDelay;

	UPROPERTY(EditAnywhere,Category="Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere,Category="Attack")
	UParticleSystem* CastingEffect;

	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* InstigatotCharacter);

public:

	UMAction_ProjectileAttack();

	virtual void StartAction_Implementation(AActor* Instigator) override;
	
};
