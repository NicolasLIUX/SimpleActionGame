// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MSaveGame.generated.h"

USTRUCT()
struct FActorSaveData
{
	GENERATED_BODY()
public:

	UPROPERTY()
	FString ActorName;

	UPROPERTY() 
	FTransform Transform;

	UPROPERTY()
	TArray<uint8> ByteData;
};

UCLASS()
class ACTIONROGUE_API UMSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
	int32 Credits;

	UPROPERTY()
	TArray<FActorSaveData> SavedActors;
};
