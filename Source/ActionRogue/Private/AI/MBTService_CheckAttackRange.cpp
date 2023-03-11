// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UMBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//check distance between ai and actor
	UBlackboardComponent* BlackboardComp=OwnerComp.GetBlackboardComponent();
	if(ensure(BlackboardComp))
	{
		AActor* TargetActor=Cast<AActor>(BlackboardComp->GetValueAsObject("TargetActor"));
		if(TargetActor)
		{
			AAIController* AIController=OwnerComp.GetAIOwner();
			if(ensure(AIController))
			{
				APawn* AIPawn=AIController->GetPawn();
				if(ensure(AIPawn))
				{
					float Distance =FVector::Distance(TargetActor->GetActorLocation(),AIPawn->GetActorLocation());

					bool bWithinRange=Distance<2000.f;
					bool  bHasLos=false;
					if(bWithinRange)
					{
						bHasLos=AIController->LineOfSightTo(TargetActor);
					}

					BlackboardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName,(bWithinRange&&bHasLos));
				}
			}
		}
	}
}
