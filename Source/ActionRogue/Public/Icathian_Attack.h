// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Icathian_Rain.h"
#include "GameFramework/Actor.h"
#include "Icathian_Attack.generated.h"

UCLASS()
class ACTIONROGUE_API AIcathian_Attack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIcathian_Attack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle Icathian_Timerhandle;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float SpawnRate;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Spawn_Icathian();

};

