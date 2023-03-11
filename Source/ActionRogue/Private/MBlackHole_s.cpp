// Fill out your copyright notice in the Description page of Project Settings.


#include "MBlackHole_s.h"

#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AMBlackHole_s::AMBlackHole_s()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp=CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent=SphereComp;
	SphereComp->SetCollisionProfileName("Projectile");

	ParticleSysComp=CreateDefaultSubobject<UParticleSystemComponent>("ParticleSysComp");
	ParticleSysComp->SetupAttachment(SphereComp);

	MovementComp=CreateDefaultSubobject<UProjectileMovementComponent>("MoveMentComp");
	MovementComp->InitialSpeed=1000.f;
	MovementComp->bRotationFollowsVelocity=true;//设置可以更新旋转方向
	MovementComp->bInitialVelocityInLocalSpace=true;
	MovementComp->ProjectileGravityScale=0.f;

	ForceComp=CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(SphereComp);

	ForceComp->Radius=500.f;
	ForceComp->ForceStrength=-200000.f;
	ForceComp->bImpulseVelChange=true;
	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
	

}

// Called when the game starts or when spawned
void AMBlackHole_s::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->IgnoreActorWhenMoving(GetInstigator(),true);
	
}

// Called every frame
void AMBlackHole_s::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void AMBlackHole_s::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentHit.AddDynamic(this,&AMBlackHole_s::OnActorHit);
}

void AMBlackHole_s::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();
}

