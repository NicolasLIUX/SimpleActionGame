// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/MWorldUserWidget.h"
#include "Components/ActorComponent.h"
#include "MInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUE_API UMInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
public:

	void PrimaryInteract();
	
public:	
	// Sets default values for this component's properties
	UMInteractionComponent();

protected:
	// Called when the game starts
	void FindBestInteratable();

	UFUNCTION(Server,Reliable)
	void ServerInteract(AActor* InFocusActor);
	
	virtual void BeginPlay() override;

	UPROPERTY()
	AActor* FocusActor;

	UPROPERTY(EditDefaultsOnly,Category="UI")
	TSubclassOf<UMWorldUserWidget> DefaultWidgetClass;

	UPROPERTY(EditDefaultsOnly,Category="Interact")
	float Trace_Radius;

	UPROPERTY(EditDefaultsOnly,Category="Interact")
	float Trace_Distance;
	
	UPROPERTY(EditDefaultsOnly,Category="Interact")
	TEnumAsByte<ECollisionChannel>  CollisionChannel;

	UPROPERTY(EditDefaultsOnly,Category="Interact")
	bool bDrawLineTraceDebug;
	

	UPROPERTY()
	UMWorldUserWidget* DefaultWidgetInstance;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
