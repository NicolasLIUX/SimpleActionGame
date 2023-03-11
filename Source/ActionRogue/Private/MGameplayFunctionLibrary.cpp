// Fill out your copyright notice in the Description page of Project Settings.


#include "MGameplayFunctionLibrary.h"

#include "MAttributeComponent.h"
#include "Android/AndroidSystemIncludes.h"

bool UMGameplayFunctionLibrary::ApplyDamage(AActor* DamageCasuser, AActor* TargetActor, float DamgeAmount)
{

	UMAttributeComponent* AttributeComp=UMAttributeComponent::GetAttribute(TargetActor);
	if(AttributeComp)
	{
		return AttributeComp->ApplyHealthChange(DamageCasuser,-DamgeAmount);
	}
	return  false;
}

bool UMGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCasuser, AActor* TargetActor, float DamgeAmount,
	const FHitResult& HitResult)
{
	if(ApplyDamage(DamageCasuser,TargetActor,DamgeAmount))
	{
		UPrimitiveComponent* HitComp= HitResult.GetComponent();
		if(HitComp&&HitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			HitComp->AddImpulseAtLocation(-HitResult.ImpactNormal*300000.f,HitResult.ImpactPoint,HitResult.BoneName);
		}
		return true;
	}
	return  false;
}
