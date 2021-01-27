// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "SteerStateManagerTestCommands.h"
#include "Jet/SteerStates/CenterSteerState.h"

#include "../Mocks/SteerStateManagerMOCK.h"
#include "../Utilities/PIESessionUtilities.h"

//Test preparation commands:

bool FSpawnASteerStateManagerMOCK::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities.spawnInPIEAnInstanceOf<ASteerStateManagerMOCK>();

		return true;
	}
	return false;
}


bool FLeftSteerASteerStateManagerMOCK::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ASteerStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ASteerStateManagerMOCK>();

		if (testManager)
		{
			testManager->steerLeft();
			return true;
		}
	}
	return false;
}


bool FRightSteerASteerStateManagerMOCK::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ASteerStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ASteerStateManagerMOCK>();

		if (testManager)
		{
			testManager->steerRight();
			return true;
		}
	}
	return false;
}


bool FCenterASteerStateManagerMOCK::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ASteerStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ASteerStateManagerMOCK>();

		if (testManager)
		{
			testManager->center();
			return true;
		}
	}
	return false;
}


bool FServerSpawnActorOfClass::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		FWorldContext serverContext = GEditor->GetWorldContexts()[1];//0 is editor, 1 is server, 2->N is clients

		if(serverContext.World()->GetNumPlayerControllers() == clientQuantity)
		{
			UE_LOG(LogTemp, Log, TEXT("Creating steer state manager..."));
			AActor* testActor = serverContext.World()->SpawnActor(anActorClass);

			APlayerController* clientController = nullptr;
			for (auto controllerIterator = serverContext.World()->GetPlayerControllerIterator(); controllerIterator; ++controllerIterator)
			{
				if(controllerIterator.GetIndex() == 1)
				{
					clientController = controllerIterator->Get();
					break;
				}
			}
			if(clientController)
			{
				testActor->SetOwner(clientController);
				UE_LOG(LogTemp, Log, TEXT("steer state manager owner set..."));
			}
			return true;
		}
	}
	return false;
}


bool FClientSteerLeftSteerStateManager::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{		
		FWorldContext serverContext = GEditor->GetWorldContexts()[1];//0 is editor, 1 is server, 2->N is clients
		if (serverContext.World()->GetNumPlayerControllers() == clientQuantity)
		{
			FWorldContext clientContext = GEditor->GetWorldContexts()[2];//0 is editor, 1 is server, 2->N is clients
			UE_LOG(LogTemp, Log, TEXT("retrieving steer state manager..."));
			ASteerStateManager* testClientManager = Cast<ASteerStateManager, AActor>(UGameplayStatics::GetActorOfClass(clientContext.World(), ASteerStateManager::StaticClass()));
			if (testClientManager)
			{
				UE_LOG(LogTemp, Log, TEXT("steering left steer state manager..."));
				testClientManager->steerLeft();
				return true;
			}
		}
	}
	return false;
}













//Test check commands:


bool FCheckSteerStateManagerCurrentState::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ASteerStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ASteerStateManagerMOCK>();
		if (testManager)
		{
			UE_LOG(LogTemp, Log, TEXT("current state: %s"), *testManager->currentState()->GetName());
			bool statesMatch = testManager->currentState()->GetClass() == expectedState;
			if (statesMatch)
			{
				test->TestTrue((TEXT("%s"), *message), statesMatch);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}

			++tickCount;
			if (tickCount > tickLimit)
			{
				test->TestTrue((TEXT("Tick limit reached. %s"), *message), statesMatch);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckSteerStateManagerCurrentStateAgainstPreviousOnSteerLeft::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ASteerStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ASteerStateManagerMOCK>();
		if (testManager)
		{
			testManager->steerLeft();
			UE_LOG(LogTemp, Log, TEXT("previous state: %s"), *(previousState ? previousState->GetName() : FString("nullptr")));
			USteerState* currentState = testManager->currentState();
			UE_LOG(LogTemp, Log, TEXT("current state: %s"), *currentState->GetName());

			bool statesMatch = currentState == previousState;
			if (statesMatch)
			{
				test->TestTrue((TEXT("%s"), *message), statesMatch);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
			previousState = currentState;

			++tickCount;
			if (tickCount > tickLimit)
			{
				test->TestTrue((TEXT("Tick limit reached. %s"), *message), statesMatch);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckSteerStateManagerCurrentStateAgainstPreviousOnSteerRight::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ASteerStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ASteerStateManagerMOCK>();
		if (testManager)
		{
			testManager->steerRight();
			UE_LOG(LogTemp, Log, TEXT("previous state: %s"), *(previousState ? previousState->GetName() : FString("nullptr")));
			USteerState* currentState = testManager->currentState();
			UE_LOG(LogTemp, Log, TEXT("current state: %s"), *currentState->GetName());

			bool statesMatch = currentState == previousState;
			if (statesMatch)
			{
				test->TestTrue((TEXT("%s"), *message), statesMatch);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
			previousState = currentState;

			++tickCount;
			if (tickCount > tickLimit)
			{
				test->TestTrue((TEXT("Tick limit reached. %s"), *message), statesMatch);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckSteerStateManagerCurrentStateAgainstPreviousOnCenter::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ASteerStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ASteerStateManagerMOCK>();
		if (testManager)
		{
			testManager->center();
			UE_LOG(LogTemp, Log, TEXT("previous state: %s"), *(previousState ? previousState->GetName() : FString("nullptr")));
			USteerState* currentState = testManager->currentState();
			UE_LOG(LogTemp, Log, TEXT("current state: %s"), *currentState->GetName());

			bool statesMatch = currentState == previousState;
			if (statesMatch)
			{
				test->TestTrue((TEXT("%s"), *message), statesMatch);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
			previousState = currentState;

			++tickCount;
			if (tickCount > tickLimit)
			{
				test->TestTrue((TEXT("Tick limit reached. %s"), *message), statesMatch);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckSteerStateManagerServerAndClientExpectedState::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		FWorldContext serverContext = GEditor->GetWorldContexts()[1];
		ASteerStateManagerMOCK* testServerManager = Cast<ASteerStateManagerMOCK, AActor>(UGameplayStatics::GetActorOfClass(serverContext.World(), ASteerStateManagerMOCK::StaticClass()));
		if(serverContext.World()->GetNumPlayerControllers() == clientQuantity && testServerManager)
		{
			FWorldContext clientContext = GEditor->GetWorldContexts()[2];//0 is editor, 1 is server, 2->N is clients
			UE_LOG(LogTemp, Log, TEXT("retrieving steer state manager for checking..."));
			ASteerStateManagerMOCK* testClientManager = Cast<ASteerStateManagerMOCK, AActor>(UGameplayStatics::GetActorOfClass(clientContext.World(), ASteerStateManagerMOCK::StaticClass()));

			bool statesMatch = false;
			if(testClientManager)
			{
				bool clientStateIsTheExpected = testClientManager->currentState()->GetClass() == expectedStateClass;
				bool serverStateIsTheExpected = testServerManager->currentState()->GetClass() == expectedStateClass;
				statesMatch = serverStateIsTheExpected && clientStateIsTheExpected;
			}

			if(statesMatch)
			{
				test->TestTrue((TEXT("The current state of server and client should be %s."), *expectedStateClass->GetName()), statesMatch);
				for(auto context : GEditor->GetWorldContexts())
				{
					context.World()->bDebugFrameStepExecution = true;
				}
				return true;
			}

			++tickCount;
			if(tickCount > tickLimit)
			{
				test->TestTrue((TEXT("The current state of server and client should be %s."), *expectedStateClass->GetName()), statesMatch);
				for(auto context : GEditor->GetWorldContexts())
				{
					context.World()->bDebugFrameStepExecution = true;
				}
				return true;
			}
		}
	}
	return false;
}






#endif //WITH_DEV_AUTOMATION_TESTS
