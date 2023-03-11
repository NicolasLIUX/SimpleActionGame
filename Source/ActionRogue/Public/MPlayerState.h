// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSaveGame.h"
#include "GameFramework/PlayerState.h"
#include "MPlayerState.generated.h"

class AMPlayerState;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged,AMPlayerState*,PlayerState,int32,NewCredits,int32,Delta);
UCLASS()
class ACTIONROGUE_API AMPlayerState : public APlayerState
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly,Category="Credits")
	int32 Credits;

public:
	UFUNCTION(BlueprintCallable,Category="Credits")
	int32 GetCredits() const;

	UFUNCTION(BlueprintCallable,Category="Credits")
	void AddCredits(int32 Delta);

	UFUNCTION(BlueprintCallable,Category="Credits")
	bool RemoveCredits(int32 Delta);
	
	UPROPERTY(BlueprintAssignable,Category="Event")
	FOnCreditsChanged OnCreditsChanged;

	UFUNCTION(BlueprintNativeEvent)
	void SavePlayerState(UMSaveGame* SaveObject);

	UFUNCTION(BlueprintNativeEvent)
	void LoadPlayerState(UMSaveGame* SaveObject);
};
