// Fill out your copyright notice in the Description page of Project Settings.


#include "MMagicProjectile.h"

#include "MAttributeComponent.h"
#include "MGameplayFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMMagicProjectile::AMMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp=CreateDefaultSubobject<USphereComponent>("SphereComp");
	// SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	// SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	// SphereComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	SphereComp->SetCollisionProfileName("Projectile");
	
	RootComponent=SphereComp;

	EffectComp=CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	Audiocomp=CreateDefaultSubobject<UAudioComponent>("AudioComp");
	Audiocomp->SetupAttachment(SphereComp);

	MovementComp=CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed=2000.0f;
	MovementComp->bRotationFollowsVelocity=true;//设置可以更新旋转方向
	MovementComp->bInitialVelocityInLocalSpace=true;
	MovementComp->ProjectileGravityScale=0.f;

	DamageValue=-20.f;

}

// Called when the game starts or when spawned
void AMMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&AMMagicProjectile::OnActorOverlap);
}

void AMMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if(OtherActor&&OtherActor!=GetInstigator())
	{
		//获取actor是否包含需要使用的组件
		UMAttributeComponent* AttributeComp=Cast<UMAttributeComponent>(OtherActor->GetComponentByClass(UMAttributeComponent::StaticClass()));
		if(AttributeComp&&HasAuthority())
		{
			AttributeComp->ApplyHealthChange(GetInstigator(),DamageValue);
			Destroy();
		}

		// if(UMGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(),OtherActor,DamageValue,SweepResult))
		// {
		// 	Destroy();
		// }
	}
	
}



