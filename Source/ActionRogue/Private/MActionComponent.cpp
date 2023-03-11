// Fill out your copyright notice in the Description page of Project Settings.


#include "MActionComponent.h"

#include "ActionRogue/ActionRogue.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"


UMActionComponent::UMActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}


void UMActionComponent::BeginPlay()
{
	
	Super::BeginPlay();

	if(GetOwner()->HasAuthority())
	{
		for(TSubclassOf<UMAction> ActionClass:DefaultActions)
		{
			AddAction(GetOwner(),ActionClass);
		}
	}
	
	
}

void UMActionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FString DebugMsg=GetNameSafe(GetOwner())+":"+ActiveGameplayTags.ToStringSimple();

	//GEngine->AddOnScreenDebugMessage(-1,0.f,FColor::Red,DebugMsg);
	for(UMAction* Action:Actions)
	{
		FColor Color=Action->IsRunning()?FColor::Blue:FColor::White;

		FString ActionMsg=FString::Printf(TEXT("[%s] Action: %s:IsRunning:%s；Outer:%s"),
			*GetNameSafe(GetOwner()),
			*Action->ActionName.ToString(),
			Action->IsRunning()?TEXT("true"):TEXT("false"),
			*GetNameSafe(Action->GetOuter()));

		LogOnScreen(this,ActionMsg,Color,0);
	}
}




void UMActionComponent::AddAction(AActor* Instigator,TSubclassOf<UMAction> ActionClass)
{
	if(!ensure(ActionClass))
	{
		return;
	}

	if(!GetOwner()->HasAuthority())
	{
		UE_LOG(LogTemp,Warning,TEXT("Client attemping to add action"));
		return;
	}
	
	UMAction* NewAction=NewObject<UMAction>(GetOwner(),ActionClass);
	if(ensure(NewAction))
	{
		NewAction->Initialize(this);
		Actions.Add(NewAction);
		if(NewAction->bAutoStart&& ensure(NewAction->CanStart(Instigator)))
		{
			NewAction->StartAction( Instigator);
		}
	}
}

void UMActionComponent::RemoveAction(UMAction* ActionReMove)
{
	if(!ensure(ActionReMove&&!ActionReMove->IsRunning()) )
	{
		return;;
	}
	Actions.Remove(ActionReMove);
}

bool UMActionComponent::StartActionByNname(AActor* Instigator, FName ActionName)
{
	for(UMAction* Action:Actions)
	{
		if(Action&&Action->ActionName==ActionName)
		{
			if(!Action->CanStart(Instigator))
			{
				FString DebugMsg=GetNameSafe(GetOwner())+":"+FString::Printf(TEXT("Failed Name"))+ActionName.ToString();

				GEngine->AddOnScreenDebugMessage(-1,0.f,FColor::Red,DebugMsg);
				continue;
			}
			
			if(!GetOwner()->HasAuthority())
			{
				ServerStartAction(Instigator,ActionName);
			}
			
			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool UMActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for(UMAction* Action:Actions)
	{
		if(Action&&Action->ActionName==ActionName)
		{
			if(Action->IsRunning())
			{
				if(!GetOwner()->HasAuthority())
				{
					ServerStopAction(Instigator,ActionName);
				}
				
				Action->StopAction(Instigator);
				return true;
			}
		}
	}
	return false;
}

bool UMActionComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething= Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	for(UMAction* Action:Actions)
	{
		if(Action)
		{
			WroteSomething|=Channel->ReplicateSubobject(Action,*Bunch,*RepFlags);
		}
	}
	return WroteSomething;
}

void UMActionComponent::ServerStartAction_Implementation(AActor* Instigator, FName ActionName)
{
	StartActionByNname(Instigator,ActionName);
}

void  UMActionComponent::ServerStopAction_Implementation(AActor* Instigator, FName ActionName) 
{
	StopActionByName(Instigator,ActionName);
}
void UMActionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMActionComponent,Actions);
}
