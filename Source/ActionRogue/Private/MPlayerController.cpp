// Fill out your copyright notice in the Description page of Project Settings.


#include "MPlayerController.h"

#include "Blueprint/UserWidget.h"

void AMPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	OnPawnChanged.Broadcast(InPawn);
}

void AMPlayerController::TogglePauseMenu()
{
	if(PauseMenuInstance&&PauseMenuInstance->IsInViewport())
	{
		PauseMenuInstance->RemoveFromParent();
		PauseMenuInstance=nullptr;

		bShowMouseCursor=false;
		SetInputMode(FInputModeGameOnly());

		return;
	}
	PauseMenuInstance=CreateWidget<UUserWidget>(this,PauseMenuClass);
	if(PauseMenuInstance)
	{
		PauseMenuInstance->AddToViewport(100);

		bShowMouseCursor=true;
		SetInputMode(FInputModeUIOnly());
	}
}

void AMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("PauseMenu",IE_Pressed,this,&AMPlayerController::TogglePauseMenu);
}
