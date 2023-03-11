// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/MPowerupActor.h"

// Sets default values
AMPowerupActor::AMPowerupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMPowerupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMPowerupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

