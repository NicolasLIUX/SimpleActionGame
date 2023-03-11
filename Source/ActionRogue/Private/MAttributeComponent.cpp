// Fill out your copyright notice in the Description page of Project Settings.


#include "MAttributeComponent.h"

#include "MGameModeBase.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UMAttributeComponent::UMAttributeComponent()
{
	
	ActorMaxHealth=100;
	Health=ActorMaxHealth;
	// ...
	SetIsReplicatedByDefault(true);
	
}



bool UMAttributeComponent::ApplyHealthChange(AActor* InstigatorActor,float Delta)
{
	float OldHealth=Health;

	float NewHealth=FMath::Clamp(Health+Delta,0.0f,ActorMaxHealth);
	float ActualDelta=NewHealth-OldHealth;
	if(GetOwner()->HasAuthority())
	{
		Health=NewHealth;
		if(ActualDelta!=0.f)
			{
			//OnHealthChanged.Broadcast(InstigatorActor,this,Health,ActualDelta);
			MulticastHealthChanged(InstigatorActor,Health,ActualDelta);//server 承担游戏中broadcast功能
			}
		if(ActualDelta<0.f&& Health==0.f)//gamemode only exist on server
		{
			AMGameModeBase* GM=GetWorld()->GetAuthGameMode<AMGameModeBase>();
			if(GM)
			{
				GM->OnActorKilled(GetOwner(),InstigatorActor);
			}
		}
	}
	
	return ActualDelta!=0.f;
}

bool UMAttributeComponent::IsAlive() const
{
	return Health>0.0f;
}

bool UMAttributeComponent::IsFullHealth()
{
	return Health==ActorMaxHealth;
}

float UMAttributeComponent::GetHealthMax()
{
		return ActorMaxHealth;
}

UMAttributeComponent* UMAttributeComponent::GetAttribute(AActor* NeedTargetActor)
{
	if(NeedTargetActor)
	{
		return Cast<UMAttributeComponent>(NeedTargetActor->GetComponentByClass(UMAttributeComponent::StaticClass()));
	}
	return nullptr;
}

bool UMAttributeComponent::IsActorAlive(AActor* Actor)
{
	UMAttributeComponent* AttributeComp=GetAttribute(Actor);
	if(AttributeComp)
	{
		return  AttributeComp->IsAlive();
	}

	return false;
}

void UMAttributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float Newhealth, float Delta)
{
	OnHealthChanged.Broadcast(InstigatorActor,this,Newhealth,Delta);
}

void UMAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Blue,TEXT("get health"));
	DOREPLIFETIME(UMAttributeComponent,Health);
	DOREPLIFETIME(UMAttributeComponent,ActorMaxHealth);
	//DOREPLIFETIME_CONDITION(UMAttributeComponent,ActorMaxHealth,COND_OwnerOnly);
	
}

