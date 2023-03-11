// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/MAction_Sprint.h"

#include "GameFramework/CharacterMovementComponent.h"

UMAction_Sprint::UMAction_Sprint()
{
	AddSpeed=400.0f;
}

void UMAction_Sprint::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	UCharacterMovementComponent* MovementComp=Cast<UCharacterMovementComponent>(Instigator->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	if(ensure(MovementComp))
	{
		MovementComp->MaxWalkSpeed+=AddSpeed;
	}
}

void UMAction_Sprint::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	UCharacterMovementComponent* MovementComp=Cast<UCharacterMovementComponent>(Instigator->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	if(MovementComp)
	{
		MovementComp->MaxWalkSpeed-=AddSpeed;
	}
}
