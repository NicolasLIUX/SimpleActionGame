// Fill out your copyright notice in the Description page of Project Settings.


#include "MInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "MGamePlayInterface.h"


// Sets default values for this component's properties
UMInteractionComponent::UMInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Trace_Radius=30.f;
	Trace_Distance=1000.f;
	CollisionChannel=ECC_WorldDynamic;
	bDrawLineTraceDebug=false;
}




// Called when the game starts
void UMInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* MyPawn=Cast<APawn>(GetOwner());
	if(MyPawn->IsLocallyControlled())
	{
		FindBestInteratable();
	}
}

void UMInteractionComponent::FindBestInteratable()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);

	AActor* Myowner=GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	Myowner->GetActorEyesViewPoint(EyeLocation,EyeRotation);
	FVector EndLocation=EyeLocation+(EyeRotation.Vector()*Trace_Distance);

	//普通的linetrace追踪方法
	// FHitResult Hit;
	// GetWorld()->LineTraceSingleByObjectType(Hit,EyeLocation,EndLocation,ObjectQueryParams);

	//使用sweep的物体检测方法

	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	
	Shape.SetSphere(Trace_Radius);
	bool bBlockingHit= GetWorld()->SweepMultiByObjectType(Hits,EyeLocation,EndLocation,FQuat::Identity,ObjectQueryParams,Shape);

	FColor LineColor=bBlockingHit?FColor::Green:FColor::Red;

	FocusActor=nullptr;
	
	for (FHitResult Hit:Hits)
	{
		AActor* HitActor=Hit.GetActor();
		if(HitActor)
		{
			if(HitActor->Implements<UMGamePlayInterface>())//Interface 检测是否使用的时候：使用UInterafacename,使用接口的时候：用IInterfacename;{
				{
					FocusActor=HitActor;
					break;
				}
		}
		DrawDebugSphere(GetWorld(),Hit.ImpactPoint,Trace_Radius,32,LineColor,false,2.0f);
	}
	if(FocusActor)
	{
		if(DefaultWidgetInstance==nullptr&&ensure(DefaultWidgetClass))
		{
			DefaultWidgetInstance=CreateWidget<UMWorldUserWidget>(GetWorld(),DefaultWidgetClass);
		}
		if(DefaultWidgetInstance)
		{
			DefaultWidgetInstance->AttachedActor=FocusActor;
			if(!DefaultWidgetInstance->IsInViewport())
			{
				DefaultWidgetInstance->AddToViewport();
			}
		}
	}
	else
	{
		if(DefaultWidgetInstance)
		{
			DefaultWidgetInstance->RemoveFromParent();
		}
	}
	
	if(bDrawLineTraceDebug)
	{
			DrawDebugLine(GetWorld(),EyeLocation,EndLocation,LineColor,false,2.0,0,2.0);
	}
	
}


void UMInteractionComponent::PrimaryInteract()
{
	ServerInteract(FocusActor);
}

void UMInteractionComponent::ServerInteract_Implementation(AActor* InFocusActor)
{
	if(InFocusActor==nullptr)
 	{
 		GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue,TEXT("FcousActor Is Nullptr"));
 		return;
 	}
 	APawn* Mypawn=Cast<APawn>(GetOwner());
 	IMGamePlayInterface::Execute_Interact(InFocusActor,Mypawn);
}
