// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MAttributeComponent.generated.h"

class UMAttributeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged,AActor*,InstigatorActor,UMAttributeComponent*,OwningComp,float,Newhealth,float,Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUE_API UMAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMAttributeComponent();

	UFUNCTION(BlueprintCallable,Category="Attributes")
	static UMAttributeComponent* GetAttribute(AActor* NeedTargetActor);

	UFUNCTION(BlueprintCallable,Category="Attributes",meta=(DisplayName="IsAlive"))
	static bool IsActorAlive(AActor* Actor);

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Replicated,Category="Attributes")
	float Health;
	//healthmax,stamina,strength
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Replicated,Category="Attributes")
	float ActorMaxHealth;

	UFUNCTION(NetMulticast,Unreliable)
	void MulticastHealthChanged(AActor*InstigatorActor,float Newhealth,float Delta);


public:

	UPROPERTY(BlueprintAssignable,Category="Health")
	FOnHealthChanged OnHealthChanged;
	
	UFUNCTION(BlueprintCallable,Category="Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor,float Delta);

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	bool IsFullHealth();

	UFUNCTION(BlueprintCallable)
	float GetHealthMax();
		
};
