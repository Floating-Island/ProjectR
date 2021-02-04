// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkedPIESessionUtilities.h"

NetworkedPIESessionUtilities::NetworkedPIESessionUtilities()
{
}

NetworkedPIESessionUtilities::~NetworkedPIESessionUtilities()
{
}

FWorldContext NetworkedPIESessionUtilities::retrieveServerWorldContext(int expectedControllersInServer)
{
	FWorldContext serverWorldContext = FWorldContext();
	const TIndirectArray<FWorldContext>& worldContexts = GEditor->GetWorldContexts();
	for (auto& worldContext : worldContexts)
	{
		int numberOfControllers = worldContext.World()->GetNumPlayerControllers();
		if (numberOfControllers == expectedControllersInServer)
		{
			serverWorldContext = worldContext;
			return serverWorldContext;
		}
	}
	return serverWorldContext;
}

bool NetworkedPIESessionUtilities::controllerQuantityInServerWorldContextIs(int expectedControllersInServer)
{
	//checks that the retrieved world isn't an empty struct (couldn't find the server with that amount of controllers spawned)...
	return retrieveServerWorldContext(expectedControllersInServer).World() ? true : false;
}

FWorldContext NetworkedPIESessionUtilities::retrieveClientWorldContext()
{
	FWorldContext clientWorldContext = FWorldContext();
	const TIndirectArray<FWorldContext>& worldContexts = GEditor->GetWorldContexts();
	for (auto& worldContext : worldContexts)
	{
		int numberOfControllers = worldContext.World()->GetNumPlayerControllers();
		if (numberOfControllers == 1)//only one controller in clients...
		{
			clientWorldContext = worldContext;
			return clientWorldContext;
		}
	}
	return clientWorldContext;
}

FWorldContext NetworkedPIESessionUtilities::retrieveClientWorldContextSafely(int expectedControllersInServer)
{
	bool ServerWorldContextIsReady = NetworkedPIESessionUtilities::controllerQuantityInServerWorldContextIs(expectedControllersInServer);
	if (ServerWorldContextIsReady)
	{
		return retrieveClientWorldContext();
	}
	else
	{
		return FWorldContext();
	}
}

bool NetworkedPIESessionUtilities::spawnActorInServerWorldOfClass(UClass* anActorClass, const FTransform actorTransform, int expectedControllersInServer)
{
	FWorldContext serverContext = NetworkedPIESessionUtilities::retrieveServerWorldContext(expectedControllersInServer);
	UWorld* serverWorld = serverContext.World();

	if (serverWorld)
	{
		APlayerController* clientController = nullptr;
		for (auto controllerIterator = serverWorld->GetPlayerControllerIterator(); controllerIterator; ++controllerIterator)
		{
			if (controllerIterator.GetIndex() == 1)
			{
				clientController = controllerIterator->Get();
				break;
			}
		}
		if (clientController)
		{
			FActorSpawnParameters spawnParameters = FActorSpawnParameters();
			spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			spawnParameters.Owner = clientController;
			AActor* actor = serverWorld->SpawnActor(anActorClass, &actorTransform, spawnParameters);
			if (IsValid(actor))
			{
				return true;
			}
		}

	}
	return false;
}

bool NetworkedPIESessionUtilities::spawnPawnInServerWorldOfClass(UClass* aPawnClass, const FTransform pawnTransform,
	int expectedControllersInServer)
{
	FWorldContext serverContext = NetworkedPIESessionUtilities::retrieveServerWorldContext(expectedControllersInServer);
	UWorld* serverWorld = serverContext.World();

	if (serverWorld)
	{
		APlayerController* clientController = nullptr;
		for (auto controllerIterator = serverWorld->GetPlayerControllerIterator(); controllerIterator; ++controllerIterator)
		{
			if (controllerIterator.GetIndex() == 1)
			{
				clientController = controllerIterator->Get();
				break;
			}
		}
		if (clientController)
		{
			FActorSpawnParameters spawnParameters = FActorSpawnParameters();
			spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			spawnParameters.Owner = clientController;
			APawn* pawn = Cast<APawn, AActor>(serverWorld->SpawnActor(aPawnClass, &pawnTransform, spawnParameters));
			if (IsValid(pawn))
			{
				clientController->Possess(pawn);
				clientController->PlayerState->SetIsSpectator(false);
				return true;
			}
		}
	}
	return false;
}
