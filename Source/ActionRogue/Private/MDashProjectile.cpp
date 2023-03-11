// Fill out your copyright notice in the Description page of Project Settings.


#include "MDashProjectile.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void AMDashProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_DetoanteDelay);
	UGameplayStatics::SpawnEmitterAtLocation(this,ImpactVFX,GetActorLocation(),GetActorRotation());

	EffectComp->DeactivateSystem();//停止系统

	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport,this,&AMDashProjectile::TeleportInstigatytor,TeleportDelay);
}

void AMDashProjectile::TeleportInstigatytor()
{
	AActor* ActorTeleport=GetInstigator();
	if(ensure(ActorTeleport))
	{
		ActorTeleport->TeleportTo(GetActorLocation(),ActorTeleport->GetActorRotation(),false,false);
	}
}

void AMDashProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_DetoanteDelay,this,&AMDashProjectile::Explode,DetonateDelay);
}

AMDashProjectile::AMDashProjectile()
{
	TeleportDelay=0.2f;
	DetonateDelay=0.2f;

	MovementComp->InitialSpeed=6000.f;
}

