// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
//#include "MActionComponent.h"
#include "MAction.generated.h"
class UMActionComponent;
/**
 * 
 */

USTRUCT()
struct FActionRepData
{
	GENERATED_BODY()

	UPROPERTY()
	bool bIsRunning;

	UPROPERTY()
	AActor* Instigator;
};


UCLASS(Blueprintable)//可以使用子类蓝图
class ACTIONROGUE_API UMAction : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="UI")
	UTexture2D* Icon;
	
	UPROPERTY(EditDefaultsOnly,Category="Tags")
	FGameplayTagContainer GrantTags;

	UPROPERTY(EditDefaultsOnly,Category="Tags")
	FGameplayTagContainer BlockedTags;

	UFUNCTION(BlueprintCallable,Category="Action")
	UMActionComponent* GetOwningComponent(	)const;

	UPROPERTY(ReplicatedUsing=OnRep_RepData)
	FActionRepData RepData;

	UPROPERTY(Replicated)
	UMActionComponent* ActionComp;

	UFUNCTION()
	void OnRep_RepData();

	UPROPERTY(Replicated)
	float TimeStarted;
public:

	void Initialize(UMActionComponent* NewActionComp);

	UPROPERTY(EditDefaultsOnly,Category="Action")
	bool bAutoStart;
	
	UPROPERTY(EditDefaultsOnly,Category="Action")
	FName ActionName;

	UFUNCTION(BlueprintNativeEvent,Category="Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent,Category="Action")
	void StopAction(AActor* Instigator);

	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintNativeEvent,Category="Action")
	bool CanStart(AActor* Instigator);

	UFUNCTION(BlueprintCallable,Category="Action")
	bool IsRunning() const;

	
	
	virtual bool IsSupportedForNetworking() const
	{
		return  true;
	}
};
