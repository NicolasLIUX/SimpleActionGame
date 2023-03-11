// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/MAction_Effect.h"

#include "MActionComponent.h"

#include "GameFramework/GameStateBase.h"

UMAction_Effect::UMAction_Effect()
{
	bAutoStart=true;
}

void UMAction_Effect::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	if(Duration>0.f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this,"StopAction",Instigator);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Duration,Delegate,Duration,false);
	}
	if(Period>0.f)
	{
		FTimerDelegate Period_Delegate;
		Period_Delegate.BindUFunction(this,"ExecutePeriodEffect",Instigator);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Period,Period_Delegate,Period,true);
	}
}

void UMAction_Effect::StopAction_Implementation(AActor* Instigator)
{
	if(GetWorld()->GetTimerManager().GetTimerRemaining(TimerHandle_Period))
	{
		ExecutePeriodEffect(Instigator);
	}
	
	Super::StopAction_Implementation(Instigator);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Duration);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Period);

	UMActionComponent* Comp=GetOwningComponent();
	if(Comp)
	{
		Comp->RemoveAction(this);
	}
	
}


float UMAction_Effect::GetTimeRemaining() const
{
	AGameStateBase* GS =GetWorld()->GetGameState<AGameStateBase>();
	if(GS)
	{
		float Endtime=TimeStarted+Duration;
		return Endtime-GS->GetServerWorldTimeSeconds();
	}

	return Duration;
}

void UMAction_Effect::ExecutePeriodEffect_Implementation(AActor* Instigator)
{
}
