// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MBTTask_RangeAttcak.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUE_API UMBTTask_RangeAttcak : public UBTTaskNode
{
	GENERATED_BODY()
public:

	UMBTTask_RangeAttcak();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere,Category="AI")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere,Category="AI")
	float MaxBulletSpread;
	
	
};
