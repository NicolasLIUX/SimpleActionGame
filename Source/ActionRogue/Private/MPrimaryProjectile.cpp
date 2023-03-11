// Fill out your copyright notice in the Description page of Project Settings.


#include "MPrimaryProjectile.h"

#include "MActionComponent.h"
#include "MAttributeComponent.h"
#include "Kismet/GameplayStatics.h"


AMPrimaryProjectile::AMPrimaryProjectile()
{
	SphereComp->SetSphereRadius(20.f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&AMPrimaryProjectile::OnActorOverlap);
	DamageValue=-20;
	
}


void AMPrimaryProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor&&OtherActor!=GetInstigator())
	{
		//获取actor是否包含需要使用的组件
		
		UMActionComponent* ActionComp=Cast<UMActionComponent>(OtherActor->GetComponentByClass(UMActionComponent::StaticClass()));
		if(ActionComp&&ActionComp->ActiveGameplayTags.HasTag(ParryTag))
		{
			MovementComp->Velocity=-MovementComp->Velocity;

			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}
		UMAttributeComponent* AttributeComp=Cast<UMAttributeComponent>(OtherActor->GetComponentByClass(UMAttributeComponent::StaticClass()));
		if(AttributeComp)
		{
			AttributeComp->ApplyHealthChange(GetInstigator(),DamageValue);
			Explode();

			if(ActionComp)
			{
				ActionComp->AddAction(GetInstigator(),BurningActionClass);
			}
		}
	}
}





