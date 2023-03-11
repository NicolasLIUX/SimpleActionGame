// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGamePlayInterface.h"
#include "GameFramework/Actor.h"
#include "MItemChest.generated.h"

class AActor;
UCLASS()
class ACTIONROGUE_API AMItemChest : public AActor,public IMGamePlayInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float TargetPitch;
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	virtual void OnActorLoaded_Implementation() override;
public:	
	// Sets default values for this actor's properties
	AMItemChest();

protected:

	UPROPERTY(ReplicatedUsing="OnRep_LidOpened",BlueprintReadOnly,SaveGame)
	bool bLidOpened;

	UFUNCTION()
	void OnRep_LidOpened() const;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* LidMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
