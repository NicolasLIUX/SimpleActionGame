// Fill out your copyright notice in the Description page of Project Settings.


#include "MGameModeBase.h"

#include "EngineUtils.h"
#include "MAttributeComponent.h"
#include "MCharacter.h"
#include "MGamePlayInterface.h"
#include "MPlayerState.h"
#include "MSaveGame.h"
#include "AI/MAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Physics/ImmediatePhysics/ImmediatePhysicsPhysX/ImmediatePhysicsSimulation_PhysX.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"


AMGameModeBase::AMGameModeBase()
{
	SpawnTimerInterval=2.0f;

	SlotName="SlotName01";
}

void AMGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots,this,&AMGameModeBase::SpawnBotTimerElapsed,SpawnTimerInterval,true);
}



void AMGameModeBase::SpawnBotTimerElapsed()
{
	int32 NrOfAliveBots=0;
	for(TActorIterator<AMAICharacter> It(GetWorld());It;++It)
	{
		AMAICharacter* Bot=*It;

		UMAttributeComponent* AttributeComp=UMAttributeComponent::GetAttribute(Bot);

		if(ensure(AttributeComp)&&AttributeComp->IsAlive())
		{
			NrOfAliveBots++;
			
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("number of spawn actor"),NrOfAliveBots);
	float MaxBotCount=0;
	if(DifficultCurve)
	{
		MaxBotCount=DifficultCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}
                                	
	if(NrOfAliveBots>=MaxBotCount)
	{
		UE_LOG(LogTemp,Warning,TEXT("over max,stop spawn"))
		return;
	}

	
	UEnvQueryInstanceBlueprintWrapper* QueryInstance=UEnvQueryManager::RunEQSQuery(this,SpawnBotQuery,this,EEnvQueryRunMode::RandomBest5Pct,nullptr);;

	if(ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this,&AMGameModeBase::OnQueryCompleted);
	}
}

void AMGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus!=EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp,Warning,TEXT("Spawn Bot EQS Failed"));
		return;
	}
	
	
	//query complete then spawn bot
	TArray<FVector> Locations =QueryInstance->GetResultsAsLocations();

	if(Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(MinionClass,Locations[0],FRotator::ZeroRotator);
	}
}


void AMGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	AMCharacter* Player=Cast<AMCharacter>(VictimActor);
	if(Player)
	{
		FTimerHandle TimerHandle_RespawnDelay;

		FTimerDelegate Delegate;
		Delegate.BindUFunction(this,"RespawnPlayerElapsed",Player->GetController());

		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay,Delegate,2.0f,false);
	}
}

void AMGameModeBase::WriteSaveGame()
{
	for(int32 i=0;i<GameState->PlayerArray.Num();i++)
	{
		AMPlayerState* PS=Cast<AMPlayerState>(GameState->PlayerArray[i]);
		if(PS)
		{
			PS->SavePlayerState(CurrentSaveGame);
		}
	}

	CurrentSaveGame->SavedActors.Empty();
	for(FActorIterator It(GetWorld());It;++It)
	{
		AActor* Actor=*It;
		if (!Actor->Implements<UMGamePlayInterface>())
		{
			continue;
		}
		FActorSaveData ActorData;
		ActorData.ActorName=Actor->GetName();
		ActorData.Transform=Actor->GetActorTransform();

		FMemoryWriter MemWriter(ActorData.ByteData);// byte data
		FObjectAndNameAsStringProxyArchive  Ar(MemWriter,true);//save variables that games need
		Ar.ArIsSaveGame=true;// only save varibles that have UPORPERTY(savegame)

		Actor->Serialize(Ar);//Converts Actor's Savegame Uproperty into binary array
		
		CurrentSaveGame->SavedActors.Add(ActorData);
	}
	
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame,SlotName,0);
}

void AMGameModeBase::LoadGame()
{
	if(UGameplayStatics::DoesSaveGameExist(SlotName,0))
	{
		CurrentSaveGame=Cast<UMSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName,0));
		if(CurrentSaveGame==nullptr)
		{
			UE_LOG(LogTemp,Warning,TEXT("Failed to load game"));
			return;
		}
	for(FActorIterator It(GetWorld());It;++It)
    	{
    		AActor* Actor=*It;
    		if (!Actor->Implements<UMGamePlayInterface>())
    		{
    			continue;
    		}
    
    		for (FActorSaveData ActorData:CurrentSaveGame->SavedActors)
    		{
    			if(ActorData.ActorName==Actor->GetName())
    			{
    				Actor->SetActorTransform(ActorData.Transform);

    				FMemoryReader MemReader(ActorData.ByteData);
    				FObjectAndNameAsStringProxyArchive  Ar(MemReader,true);
    				Ar.ArIsSaveGame=true;

    				Actor->Serialize(Ar);//Converts binary array into Actor's Savegame Uproperty

    				IMGamePlayInterface::Execute_OnActorLoaded(Actor);
    				break;
    			}
    		}
    	}
	}
	else
	{
		CurrentSaveGame=Cast<UMSaveGame>(UGameplayStatics::CreateSaveGameObject(UMSaveGame::StaticClass()));
	}

	
}

void AMGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);//可以在游戏最开始的时候进行
	
	LoadGame();
}

void AMGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	AMPlayerState* PS=NewPlayer->GetPlayerState<AMPlayerState>();
	if(PS)
	{
		PS->LoadPlayerState(CurrentSaveGame);
	}
}

void AMGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if(ensure(Controller))
	{
		Controller->UnPossess();

		RestartPlayer(Controller);
	}
}
