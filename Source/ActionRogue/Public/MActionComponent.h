// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayTaskTypes.h"
#include "MAction.h"
#include "Action/MAction_Effect.h"
#include "Components/ActorComponent.h"
#include "MActionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionStateChanged,UMActionComponent*, OwningComp,UMAction*, Action);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUE_API UMActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMActionComponent();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tages")
	FGameplayTagContainer ActiveGameplayTags;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintReadOnly,Replicated)
	TArray<UMAction*> Actions;

	UPROPERTY(EditAnywhere,Category="Actions")
	TArray<TSubclassOf<UMAction>> DefaultActions;

	UFUNCTION(Server,Reliable)
	void ServerStartAction(AActor* Instigator,FName ActionName);

	UFUNCTION(Server, Reliable)
	void ServerStopAction(AActor* Instigator, FName ActionName) ;

public:	
	
	UFUNCTION(BlueprintCallable,Category="Action")
	void AddAction(AActor* Instigator,TSubclassOf<UMAction> ActionClass);

	UFUNCTION(BlueprintCallable,Category="Action")
	void RemoveAction(UMAction* ActionRemove);

	UFUNCTION(BlueprintCallable,Category="Action")
	bool StartActionByNname(AActor* Instigator,FName ActionName);

	UFUNCTION(BlueprintCallable,Category="Action")
	bool StopActionByName(AActor* Instigator,FName ActionName);

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionStarted;

	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionStopped;
};
