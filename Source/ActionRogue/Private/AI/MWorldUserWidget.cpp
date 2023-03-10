// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MWorldUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

void UMWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(!IsValid(AttachedActor))
	{
		RemoveFromParent();
		return;
	}

	FVector2D ScreenPosition;
	if (UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(),AttachedActor->GetActorLocation()+WorldOffset,ScreenPosition))
	{
		float Scale=UWidgetLayoutLibrary::GetViewportScale(this);
		
		ScreenPosition/=Scale;

		if(ParentsSizeBox)
		{
			ParentsSizeBox->SetRenderTranslation(ScreenPosition);
		}
	}
}
