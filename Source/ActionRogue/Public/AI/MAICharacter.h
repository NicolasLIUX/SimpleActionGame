// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MAttributeComponent.h"
#include "MWorldUserWidget.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "MAICharacter.generated.h"

UCLASS()
class ACTIONROGUE_API AMAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMAICharacter();

protected:

	UPROPERTY(VisibleAnywhere,Category="Effects")
	FName TimeToHitParamName;
	
	UPROPERTY(EditAnywhere,Category="Components")
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UMAttributeComponent* AttributeComp;

	UMWorldUserWidget* ActiveHealthBar;

	UPROPERTY(EditDefaultsOnly,Category="UI")
	TSubclassOf<UMWorldUserWidget> HealthBarWidgetClass;

	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor,UMAttributeComponent* OwningComp,float Newhealth,float Delta);

	void SetTargetActor(AActor* NewActor);
};
