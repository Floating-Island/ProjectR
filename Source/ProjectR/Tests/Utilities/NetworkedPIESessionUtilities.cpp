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
	UE_LOG(LogTemp, Log, TEXT("Network Commands: Attempting to retrieve the server world context..."));
	FWorldContext serverWorldContext = FWorldContext();
	const TIndirectArray<FWorldContext>& worldContexts = GEditor->GetWorldContexts();
	UE_LOG(LogTemp, Log, TEXT("Network Commands: listing world contexts..."));
	for (auto& worldContext : worldContexts)
	{
		int numberOfControllers = worldContext.World()->GetNumPlayerControllers();
		UE_LOG(LogTemp, Log, TEXT("Network Commands: number of controllers in world context: %d."), numberOfControllers);
		if (numberOfControllers == expectedControllersInServer)
		{
			UE_LOG(LogTemp, Log, TEXT("Network Commands: Server world context found!"));
			serverWorldContext = worldContext;
			return serverWorldContext;
		}
	}
	UE_LOG(LogTemp, Log, TEXT("Network Commands: Couldn't find the server world context, retrieving empty world context..."));
	return serverWorldContext;
}

bool NetworkedPIESessionUtilities::controllerQuantityInServerWorldContextIs(int expectedControllersInServer)
{
	//checks that the retrieved world isn't an empty struct (couldn't find the server with that amount of controllers spawned)...
	UE_LOG(LogTemp, Log, TEXT("Network Commands: Checking that the server world context has the expected controllers..."));
	return retrieveServerWorldContext(expectedControllersInServer).World() ? true : false;
}

FWorldContext NetworkedPIESessionUtilities::retrieveClientWorldContext()
{
	UE_LOG(LogTemp, Log, TEXT("Network Commands: Attempting to retrieve the client world context..."));
	FWorldContext clientWorldContext = FWorldContext();
	const TIndirectArray<FWorldContext>& worldContexts = GEditor->GetWorldContexts();
	UE_LOG(LogTemp, Log, TEXT("Network Commands: listing world contexts..."));
	for (auto& worldContext : worldContexts)
	{
		int numberOfControllers = worldContext.World()->GetNumPlayerControllers();
		UE_LOG(LogTemp, Log, TEXT("Network Commands: number of controllers in world context: %d."), numberOfControllers);
		if (numberOfControllers == 1)//only one controller in clients...
		{
			UE_LOG(LogTemp, Log, TEXT("Network Commands: Client world context found!"));
			clientWorldContext = worldContext;
			return clientWorldContext;
		}
	}
	UE_LOG(LogTemp, Log, TEXT("Network Commands: Couldn't find the client world context, retrieving empty world context..."));
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
		UE_LOG(LogTemp, Log, TEXT("Creating actor of class %s..."), *anActorClass->GetName());


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
				UE_LOG(LogTemp, Log, TEXT("actor of class %s created!"), *anActorClass->GetName());
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
		UE_LOG(LogTemp, Log, TEXT("Creating pawn of class %s..."), *aPawnClass->GetName());

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
				UE_LOG(LogTemp, Log, TEXT("Created and possessed pawn of class %s!"), *aPawnClass->GetName());
				return true;
			}
		}
	}
	return false;
}
