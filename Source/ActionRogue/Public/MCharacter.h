// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MActionComponent.h"
#include "MAttributeComponent.h"

#include "MInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "MCharacter.generated.h"

UCLASS()
class ACTIONROGUE_API AMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMCharacter();
protected:

	UPROPERTY(VisibleAnywhere,Category="Effects")
	FName HandleSocketName;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BlackHoleClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> DashClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Components")
	UMInteractionComponent* InteractionComp;

	UPROPERTY(EditAnywhere,Category="Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UMAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere,Category="Effects")
	FName TimeToHitParamName;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UMActionComponent* ActionComp;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveForward(float value);

	UFUNCTION()
	void MoveRight(float value);

	UFUNCTION()
	void PrimaryAttack();

	void PrimaryInteract();
	

	UFUNCTION()
	void BlackHoleAttack();

	UFUNCTION()
	void DashAttcak();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor,UMAttributeComponent* OwningComp,float Newhealth,float Delta);

	virtual void PostInitializeComponents() override;

	virtual FVector GetPawnViewLocation() const override;

	UFUNCTION()
	void SprintStart();

	UFUNCTION()
	void SprintStop();

};



