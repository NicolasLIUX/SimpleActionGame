// Fill out your copyright notice in the Description page of Project Settings.


#include "Icathian_Attack.h"

// Sets default values
AIcathian_Attack::AIcathian_Attack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnRate=1.0f;

}

// Called when the game starts or when spawned
void AIcathian_Attack::BeginPlay()
{
	Super::BeginPlay();
	FTimerDelegate Icathian_Delegate;
	Icathian_Delegate.BindUFunction(this,"Spawn_Icathian") ; 
	GetWorldTimerManager().SetTimer(Icathian_Timerhandle,Icathian_Delegate,SpawnRate,true);
	
}

// Called every frame
void AIcathian_Attack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIcathian_Attack::Spawn_Icathian()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass,GetActorLocation() , GetActorRotation(), SpawnParams);
}

