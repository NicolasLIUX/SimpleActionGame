// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Icathian_Rain.generated.h"

UCLASS()
class ACTIONROGUE_API AIcathian_Rain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIcathian_Rain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="Distance")
	FVector AddVector;

	
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="Distance")
	float Height;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="Distance")
	float Length;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="SphereComp")
	USphereComponent* SphereComp;
	
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="SphereComp")
	UParticleSystemComponent* ParticleSysComp;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="TimeLine")
	UTimelineComponent* TimelineComp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="TimeLine")
	UCurveFloat* CurveFloat;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<AActor> AttackActor;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float PlayRate;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float DamageValue;
	
	FTimerHandle Icathian_Timerhandle;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	bool bDrawDebug;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	FVector Triangle(FVector StartLoc,FVector EndLoc);
	
	FVector StartLocation;
	FVector Triangle_Location;
	FVector TargetLocation;
	bool Reverse_Tri;
	float Length_Tri;
	AActor* AttackAcotrIns;
	
	UFUNCTION()
	void OnTimelineTick(float Output);

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};






