// Fill out your copyright notice in the Description page of Project Settings.


#include "MPlayerState.h"

int32 AMPlayerState::GetCredits() const
{
	return Credits;
}

void AMPlayerState::AddCredits(int32 Delta)
{
	if(!ensure(Delta>0.0f))
	{
		return;
	}
	Credits+=Delta;

	OnCreditsChanged.Broadcast(this,Credits,Delta);
}

bool AMPlayerState::RemoveCredits(int32 Delta)
{
	if(!ensure(Delta>0.0f))
	{
		return false;
	}
	if(Credits<Delta)
	{
		return false;
	}
	Credits-=Delta;

	OnCreditsChanged.Broadcast(this,Credits,Delta);
	return true;
}

void AMPlayerState::SavePlayerState_Implementation(UMSaveGame* SaveObject)
{
	if(SaveObject)
	{
		SaveObject->Credits=Credits;
	}
}

void AMPlayerState::LoadPlayerState_Implementation(UMSaveGame* SaveObject)
{
	if(SaveObject)
	{
		Credits=SaveObject->Credits;
	}
}