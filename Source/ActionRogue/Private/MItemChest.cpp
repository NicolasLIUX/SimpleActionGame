// Fill out your copyright notice in the Description page of Project Settings.


#include "MItemChest.h"

#include "Engine/StaticMeshSocket.h"
#include "Net/UnrealNetwork.h"

void AMItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	bLidOpened=!bLidOpened;
	OnRep_LidOpened();
}

void AMItemChest::OnActorLoaded_Implementation()
{
	OnRep_LidOpened();
}

// Sets default values
AMItemChest::AMItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent=BaseMesh;

	LidMesh=CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);
	TargetPitch=110;

	SetReplicates(true);
	
}

// Called when the game starts or when spawned
void AMItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMItemChest::OnRep_LidOpened() const
{
	float CurrPitch=bLidOpened?TargetPitch:0;
	LidMesh->SetRelativeRotation(FRotator(CurrPitch,0,0));
}

void AMItemChest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Blue,TEXT("get life"));
	DOREPLIFETIME(AMItemChest,bLidOpened);
}

