// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
/**
 * 
 */
class PROJECTR_API NetworkedPIESessionUtilities
{
public:
	NetworkedPIESessionUtilities();
	~NetworkedPIESessionUtilities();


	/**
	 * Even if it doesn't find the server context, it'll retrieve an empty world context.
	 * After retrieving it, you should check that its World() isn't a nullptr...
	 */
	static FWorldContext retrieveServerWorldContext(int expectedControllersInServer);

	
	/**
	 * tries to retrieve the server world context 
	 */
	static bool controllerQuantityInServerWorldContextIs(int expectedControllersInServer);


	/**
	 * This method supposes that a client context has only one controller, so it should be used after acquiring the server context. That way,
	 * you are sure that the server context has all the controllers and you didn't retrieve by accident the server context while it still had only one controller created...
	 * Even if it doesn't find the client context, it'll retrieve an empty world context.
	 * After retrieving it, you should check that its World() isn't a nullptr...
	 */
	static FWorldContext retrieveClientWorldContext();


	/**
	 * Safely retrieve the client world context.
	 * It uses retrieveClientWorldContext() but it checks that the server world context exists and already has the expected controllers.
	 * Even if it doesn't find the client context, it'll retrieve an empty world context.
	 * After retrieving it, you should check that its World() isn't a nullptr...
	 */
	static FWorldContext retrieveClientWorldContextSafely(int expectedControllersInServer);
	
	
	/**
	 * Looks for the server context, retrieves its world, looks for the client controller, creates the pawn and makes the controller possess it.
	 * The pawn owner will be the client controller. This is because the pawn needs a connection to be able to make remote procedure calls (RPCs).
	 * Returns whether it was able to find the server context and spawn the pawn possessed.
	 */
	template<class aPawnClass>
	static bool spawnPawnInServerWorldOfClass(int expectedControllersInServer);

	
	/**
	 * Looks for the server context, retrieves its world, looks for the client controller, creates the actor and makes the controller its owner.
	 * The actor owner will be the client controller because the actor needs a connection to be able to make remote procedure calls (RPCs).
	 * Returns whether it was able to find the server context and create the actor.
	 */
	template<class anActorClass>
	static bool spawnActorInServerWorldOfClass(int expectedControllersInServer);
};

template <class aPawnClass>
bool NetworkedPIESessionUtilities::spawnPawnInServerWorldOfClass(int expectedControllersInServer)
{
	FWorldContext serverContext = NetworkedPIESessionUtilities::retrieveServerWorldContext(expectedControllersInServer);
	UWorld* serverWorld = serverContext.World();

	if(serverWorld)
	{
		UE_LOG(LogTemp, Log, TEXT("Creating pawn of class %s..."), *aPawnClass::StaticClass()->GetName());
		
		APlayerController* clientController = nullptr;
		for (auto controllerIterator = serverWorld->GetPlayerControllerIterator(); controllerIterator; ++controllerIterator)
		{
			if(controllerIterator.GetIndex() == 1)
			{
				clientController = controllerIterator->Get();
				break;
			}
		}
		if(clientController)
		{
			FActorSpawnParameters spawnParameters = FActorSpawnParameters();
			spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			spawnParameters.Owner = clientController;
			aPawnClass* testPawn = serverWorld->SpawnActor<aPawnClass>(FVector(1000), FRotator(0), spawnParameters);
			
			clientController->Possess(testPawn);
			clientController->PlayerState->SetIsSpectator(false);
			UE_LOG(LogTemp, Log, TEXT("Created and possessed pawn of class %s!"), *aPawnClass::StaticClass()->GetName());
			return true;
		}
	}
	return false;
}

template <class anActorClass>
bool NetworkedPIESessionUtilities::spawnActorInServerWorldOfClass(int expectedControllersInServer)
{

	FWorldContext serverContext = NetworkedPIESessionUtilities::retrieveServerWorldContext(expectedControllersInServer);
	UWorld* serverWorld = serverContext.World();

	if(serverWorld)
	{
		UE_LOG(LogTemp, Log, TEXT("Creating actor of class %s..."), *anActorClass::StaticClass()->GetName());
		

		APlayerController* clientController = nullptr;
		for (auto controllerIterator = serverWorld->GetPlayerControllerIterator(); controllerIterator; ++controllerIterator)
		{
			if(controllerIterator.GetIndex() == 1)
			{
				clientController = controllerIterator->Get();
				break;
			}
		}
		if(clientController)
		{
			FActorSpawnParameters spawnParameters = FActorSpawnParameters();
			spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			spawnParameters.Owner = clientController;
			anActorClass* testActor = serverWorld->SpawnActor<anActorClass>(spawnParameters);
			UE_LOG(LogTemp, Log, TEXT("actor of class %s created!"), *anActorClass::StaticClass()->GetName());
			return true;
		}
		
	}
	return false;
}
