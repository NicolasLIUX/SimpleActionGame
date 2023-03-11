// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/MAction_ProjectileAttack.h"

#include "MCharacter.h"
#include "Kismet/GameplayStatics.h"


UMAction_ProjectileAttack::UMAction_ProjectileAttack()
{
	HandSocketName="Muzzle_01";
	AttackAnimDelay=0.2f;
}

void UMAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACharacter* Character=Cast<ACharacter>(Instigator);
	if(Character)
	{
		Character->PlayAnimMontage(AttackAnim);
		UGameplayStatics::SpawnEmitterAttached(CastingEffect,Character->GetMesh(),HandSocketName,FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::SnapToTarget);

		if(Character->HasAuthority())
		{
			FTimerHandle TimerHandle_AttackDelay;
			FTimerDelegate Delegate;
			Delegate.BindUFunction(this,"AttackDelay_Elapsed",Character);
            
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay,Delegate,AttackAnimDelay,false);
		}
	}
}

void UMAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatotCharacter)
{
	
	if(ensureAlways(ProjectileClass))//ensure可以判断内容是否存在，存在返回真，不存在则会在此处产生断点(只产生一次)，ensurealways可以多次触发
		{
		FVector HandLocation=InstigatotCharacter->GetMesh()->GetSocketLocation("Muzzle_01");

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator=InstigatotCharacter;

		FCollisionShape Shape;
		Shape.SetSphere(20.f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(InstigatotCharacter);

		FCollisionObjectQueryParams ObjectParams;
		ObjectParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectParams.AddObjectTypesToQuery(ECC_Pawn);

		FVector TraceStart=InstigatotCharacter->GetPawnViewLocation();

		FVector TraceEnd=TraceStart+(InstigatotCharacter->GetControlRotation().Vector()*5000);

		FHitResult Hit;
		if(GetWorld()->SweepSingleByObjectType(Hit,TraceStart,TraceEnd,FQuat::Identity,ObjectParams,Shape,Params))
		{
			TraceEnd=Hit.ImpactPoint;
		}

		FRotator ProjRotation=FRotationMatrix::MakeFromX(TraceEnd-HandLocation).Rotator();

		FTransform SpawmTM=FTransform(ProjRotation,HandLocation);
		GetWorld()->SpawnActor<AActor>(ProjectileClass,HandLocation , ProjRotation, SpawnParams);
		}
	StopAction(InstigatotCharacter);
}