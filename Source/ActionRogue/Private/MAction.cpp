// Fill out your copyright notice in the Description page of Project Settings.


#include "MAction.h"

#include <chrono>

#include "MActionComponent.h"
#include "ActionRogue/ActionRogue.h"
#include "Net/UnrealNetwork.h"

void UMAction::StartAction_Implementation(AActor* Instigator)
{
	LogOnScreen(this,FString::Printf(TEXT("Started:%s"),*ActionName.ToString()),FColor::Green);
	UMActionComponent* Comp=GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantTags);

	RepData.bIsRunning=true;
	RepData.Instigator=Instigator;

	if(GetOwningComponent()->GetOwnerRole()==ROLE_Authority)
	{
		TimeStarted=GetWorld()->GetTimeSeconds();
	}

	GetOwningComponent()->OnActionStarted.Broadcast(GetOwningComponent(),this);
}

void UMAction::StopAction_Implementation(AActor* Instigator)
{
	LogOnScreen(this,FString::Printf(TEXT("Stopped:%s"),*ActionName.ToString()),FColor::White);
	//ensureAlways(bIsRunning);
	
	UMActionComponent* Comp=GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantTags);

	RepData.bIsRunning=false;
	RepData.Instigator=Instigator;

	GetOwningComponent()->OnActionStopped.Broadcast(GetOwningComponent(),this);
}



UWorld* UMAction::GetWorld() const
{
	//创建新的actionComp时需要重新設置getworld，以便访问getworld里的函数。
	AActor* Comp=Cast<AActor>(GetOuter());
	if(Comp)
	{
		return  Comp->GetWorld();
	}
	return nullptr;
}



bool UMAction::CanStart_Implementation(AActor* Instigator)
{
	if(IsRunning())
	{
		return  false;
	}
	UMActionComponent* Comp=GetOwningComponent();
	if(Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return  false;
	}
	return  true;
}

UMActionComponent* UMAction::GetOwningComponent() const
{
	//AActor* Actor=Cast<AActor>(GetOuter());
	//return Actor->GetComponentByClass(UMActionComponent::StaticClass());
	return  ActionComp;
}

void UMAction::OnRep_RepData()
{
	if(RepData.bIsRunning)
	{
		StartAction(RepData.Instigator);
	}
	else
	{
		StopAction(RepData.Instigator);
	}
}

void UMAction::Initialize(UMActionComponent* NewActionComp)
{
	ActionComp=NewActionComp;
}

bool UMAction::IsRunning() const
{
	return RepData.bIsRunning;
}


void UMAction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMAction,RepData);
	DOREPLIFETIME(UMAction,TimeStarted);
	DOREPLIFETIME(UMAction,ActionComp);
}
