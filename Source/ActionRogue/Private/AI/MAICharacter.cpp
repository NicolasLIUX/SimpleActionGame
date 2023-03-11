// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMAICharacter::AMAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp=CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AttributeComp=CreateDefaultSubobject<UMAttributeComponent>("AttributeComp");

	TimeToHitParamName="TimeToHit";
	

	AutoPossessAI=EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this,&AMAICharacter::OnPawnSeen);

	AttributeComp->OnHealthChanged.AddDynamic(this,&AMAICharacter::OnHealthChanged);
}

void AMAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);
}

void AMAICharacter::OnHealthChanged(AActor* InstigatorActor, UMAttributeComponent* OwningComp, float Newhealth,
	float Delta)
{
	if(Delta<=0.f)
	{
		if(InstigatorActor!=this)
		{
			SetTargetActor(InstigatorActor);
		}

		if(ActiveHealthBar==nullptr)
		{
			ActiveHealthBar=CreateWidget<UMWorldUserWidget>(GetWorld(),HealthBarWidgetClass);
            
			if(ActiveHealthBar)
			{
				ActiveHealthBar->AttachedActor=this;
				ActiveHealthBar->AddToViewport();
			}
		}

		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName,GetWorld()->TimeSeconds);
		
		if(Newhealth<=0.f)
		{
			AAIController* AIC=Cast<AAIController>(GetController());
			if(AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}

			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();
			
			SetLifeSpan(10.f);
		}
	}
}

void AMAICharacter::SetTargetActor(AActor* NewActor)
{
	AAIController* AIController=Cast<AAIController>(GetController());
	if(AIController)
	{
		UBlackboardComponent* BlackBoardComp=AIController->GetBlackboardComponent();

		BlackBoardComp->SetValueAsObject("TargetActor",NewActor);

		//DrawDebugString(GetWorld(),GetActorLocation(),"PlayerLoction",nullptr,FColor::Red,4.0f,true);
	}
}



