// Fill out your copyright notice in the Description page of Project Settings.


#include "MExplosiveBarrel.h"

#include "DrawDebugHelpers.h"

// Sets default values
AMExplosiveBarrel::AMExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp=CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetSimulatePhysics(true);
	RootComponent=MeshComp;

	ForceComp=CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(MeshComp);

	ForceComp->Radius=750.f;
	ForceComp->ImpulseStrength=2500.f;
	ForceComp->bImpulseVelChange=true;

	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);

}

// Called when the game starts or when spawned
void AMExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MeshComp->OnComponentHit.AddDynamic(this,&AMExplosiveBarrel::OnActorHit);//需要绑定的函数参数可以在需要绑定的事件的navigate中定义的前缀中寻找。
	//需要绑定的函数必须使用Ufunction暴露在ue中。
}

void AMExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();

	UE_LOG(LogTemp,Warning,TEXT("other actor:%s"),*GetNameSafe(OtherActor));//处理string类型需要使用地址。

	FString Combinedstring=FString::Printf(TEXT("Hit at location:"),*Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(),Hit.ImpactPoint,Combinedstring,nullptr,FColor::Red,2.0f,true);
}

	