// Fill out your copyright notice in the Description page of Project Settings.


#include "Icathian_Rain.h"

#include "DrawDebugHelpers.h"
#include "MAttributeComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Containers/Array.h"

// Sets default values
AIcathian_Rain::AIcathian_Rain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	AddVector=FVector(0,0,0);
	Height=100.f;
	PlayRate=1.0f;
	Length=200;
	DamageValue=50.f;
	bDrawDebug=false;
	Reverse_Tri=false;
	
	SphereComp=CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetSphereRadius(30.f);
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent=SphereComp;

	ParticleSysComp=CreateDefaultSubobject<UParticleSystemComponent>("ParticleSysComp");
	ParticleSysComp->SetupAttachment(SphereComp);

	TimelineComp=CreateDefaultSubobject<UTimelineComponent>("TimelineComp");
	
	
}

// Called when the game starts or when spawned
void AIcathian_Rain::BeginPlay()
{
	Super::BeginPlay();
	StartLocation=GetActorLocation();
	Height=FMath::RandRange(Height,2*Height);
	Reverse_Tri=FMath::RandBool();
	Length_Tri=FMath::RandRange(0.0,Length);
	
	TArray<AActor*> AttackActorArr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AttackActor,AttackActorArr);
         
	int LastIndex=AttackActorArr.Num()-1;
	int RandonIndex=FMath::RandRange(0,LastIndex);
	AttackAcotrIns=AttackActorArr[RandonIndex];
	if(IsValid(AttackAcotrIns))
	{
		FOnTimelineFloat TimelineTickDelegate;
     	TimelineTickDelegate.BindUFunction(this,"OnTimelineTick");
     	TimelineComp->AddInterpFloat(CurveFloat,TimelineTickDelegate);
     	TimelineComp->SetPlayRate(PlayRate);
     	TimelineComp->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
     	TimelineComp->SetLooping(false);
     	TimelineComp->Play();
		// TargetLocation=AttackAcotrIns->GetActorLocation();
		// Triangle_Location=Triangle(StartLocation,TargetLocation);
	}
	
	
	SetLifeSpan(1.f);
}

// Called every frame
void AIcathian_Rain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

FVector AIcathian_Rain::Triangle( FVector StartLoc,FVector EndLoc)
{
	float Distance=FVector::Distance(StartLoc,EndLoc);
	FRotator Rotation_To_Tar=UKismetMathLibrary::FindLookAtRotation(StartLoc,EndLoc);
	FVector Forword_To_Tar=UKismetMathLibrary::GetForwardVector(Rotation_To_Tar);

	AddVector.Z+=Height;
	FVector Tri_Rotation=UKismetMathLibrary::GetForwardVector(FRotator(Rotation_To_Tar.Pitch,Rotation_To_Tar.Yaw-90.f,Rotation_To_Tar.Roll));
	
	float Reverse= UKismetMathLibrary::SelectFloat(1.0,-1.0,Reverse_Tri);
	FVector Tri_Location=StartLoc+ Forword_To_Tar*Distance/2+Tri_Rotation*Length_Tri*Reverse+AddVector;

	if(bDrawDebug)
	{
		DrawDebugLine(GetWorld(),StartLoc,EndLoc,FColor::White,false,3,0,3);
		DrawDebugLine(GetWorld(),StartLoc,Tri_Location,FColor::Red,false,3,0,3);
		DrawDebugLine(GetWorld(),Tri_Location,EndLoc,FColor::Blue,false,3,0,3);
	}
	return Tri_Location;
}

void AIcathian_Rain::OnTimelineTick(float Output)
{
	TargetLocation=AttackAcotrIns->GetActorLocation();
	DrawDebugString(GetWorld(),StartLocation,"start location",0,FColor::Red,1.f);
	DrawDebugString(GetWorld(),AttackAcotrIns->GetActorLocation(),"actor location",0,FColor::Red,1.f);
	Triangle_Location=Triangle(StartLocation,TargetLocation);
	//GetWorld()->SpawnActor();
	FVector AToBVector=FMath::Lerp(StartLocation,Triangle_Location,Output);
	FVector BToCVector=FMath::Lerp(Triangle_Location,TargetLocation,Output);
	FVector Icathian_Location=FMath::Lerp(AToBVector,BToCVector,Output);
	SetActorLocation(Icathian_Location);
}

void AIcathian_Rain::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&AIcathian_Rain::OnActorOverlap);
}

void AIcathian_Rain::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor&&OtherActor!=GetInstigator())
	{
		//获取actor是否包含需要使用的组件
		UMAttributeComponent* AttributeComp=Cast<UMAttributeComponent>(OtherActor->GetComponentByClass(UMAttributeComponent::StaticClass()));
		AttributeComp->ApplyHealthChange(GetInstigator(),DamageValue);
		Destroy();
	}
}


