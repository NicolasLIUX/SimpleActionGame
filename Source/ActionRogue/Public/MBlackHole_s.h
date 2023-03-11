// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MBlackHole_s.generated.h"

class URadialForceComponent;
UCLASS()
class ACTIONROGUE_API AMBlackHole_s : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UParticleSystemComponent* ParticleSysComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	URadialForceComponent* ForceComp;
	
public:	
	// Sets default values for this actor's properties
	AMBlackHole_s();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void PostInitializeComponents() override;

	UFUNCTION()//可以是函数暴露在ue中，从而使函数正确的绑定
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
