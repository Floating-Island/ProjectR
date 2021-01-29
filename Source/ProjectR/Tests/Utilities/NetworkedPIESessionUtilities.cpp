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
	for (auto& worldContext: worldContexts)
	{
		int numberOfControllers = worldContext.World()->GetNumPlayerControllers();
		UE_LOG(LogTemp, Log, TEXT("Network Commands: number of controllers in world context: %d."), numberOfControllers);
		if(numberOfControllers == expectedControllersInServer)
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
	return retrieveServerWorldContext(expectedControllersInServer).World()? true : false;
}

FWorldContext NetworkedPIESessionUtilities::retrieveClientWorldContext()
{
	UE_LOG(LogTemp, Log, TEXT("Network Commands: Attempting to retrieve the client world context..."));
	FWorldContext clientWorldContext = FWorldContext();
	const TIndirectArray<FWorldContext>& worldContexts = GEditor->GetWorldContexts();
	UE_LOG(LogTemp, Log, TEXT("Network Commands: listing world contexts..."));
	for (auto& worldContext: worldContexts)
	{
		int numberOfControllers = worldContext.World()->GetNumPlayerControllers();
		UE_LOG(LogTemp, Log, TEXT("Network Commands: number of controllers in world context: %d."), numberOfControllers);
		if(numberOfControllers == 1)//only one controller in clients...
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
	if(ServerWorldContextIsReady)
	{
		return retrieveClientWorldContext();
	}
	else
	{
		return FWorldContext();
	}
}
