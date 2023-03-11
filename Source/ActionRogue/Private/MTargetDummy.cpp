// Fill out your copyright notice in the Description page of Project Settings.


#include "MTargetDummy.h"

#include <corecrt_io.h>

// Sets default values
AMTargetDummy::AMTargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AttributeComp=CreateDefaultSubobject<UMAttributeComponent>("AttributeComp");
	
	StaticMesh=CreateDefaultSubobject<UStaticMeshComponent>("staticMesh");
	RootComponent=StaticMesh;

	AttributeComp->OnHealthChanged.AddDynamic(this,&AMTargetDummy::OnHealthChanged);
}

// Called when the game starts or when spawned
void AMTargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMTargetDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMTargetDummy::OnHealthChanged(AActor* InstigatorActor, UMAttributeComponent* OwningComp, float Newhealth,
	float Delta)
{
	if(Delta<0)
	{
		StaticMesh->SetScalarParameterValueOnMaterials("TimeToHit",GetWorld()->TimeSeconds);
	}
}

