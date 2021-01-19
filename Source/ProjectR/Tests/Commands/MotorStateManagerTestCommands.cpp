// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "MotorStateManagerTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "../Mocks/MotorStateManagerMOCK.h"
#include "Jet/MotorStates/NeutralMotorState.h"
#include "Jet/MotorStates/AcceleratingMotorState.h"
#include "Jet/MotorStates/ReversingMotorState.h"


//Test preparation commands:

bool FSpawnAMotorStateManager::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities.spawnInPIEAnInstanceOf<AMotorStateManagerMOCK>();
		
		return true;
	}

	return false;
}


bool FSpawnAMotorStateManagerAndAccelerateIt::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.spawnInPIEAnInstanceOf<AMotorStateManagerMOCK>();

		testManager->accelerate();
		
		return true;
	}

	return false;
}


bool FSpawnAMotorStateManagerAndBrakeIt::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.spawnInPIEAnInstanceOf<AMotorStateManagerMOCK>();

		testManager->brake();
		
		return true;
	}

	return false;
}


bool FSpawnAMotorStateManagerAndNeutralizeIt::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.spawnInPIEAnInstanceOf<AMotorStateManagerMOCK>();

		testManager->brake();//first change it to another state.
		testManager->neutralize();
		
		return true;
	}

	return false;
}


bool FSpawnAMotorStateManagerBrakeAccelerateAndNeutralizeIt::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.spawnInPIEAnInstanceOf<AMotorStateManagerMOCK>();

		testManager->brake();
		testManager->accelerate();
		testManager->neutralize();
		
		return true;
	}

	return false;
}


bool FServerSpawnMotorStateManager::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		FWorldContext serverContext = GEditor->GetWorldContexts()[1];//0 is editor, 1 is server, 2->N is clients

		if(serverContext.World()->GetNumPlayerControllers() == clientQuantity)
		{
			UE_LOG(LogTemp, Log, TEXT("Creating motor state manager..."));
			AMotorStateManagerMOCK* testManager = serverContext.World()->SpawnActor<AMotorStateManagerMOCK>();

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
				testManager->SetOwner(clientController);
				UE_LOG(LogTemp, Log, TEXT("motor state manager owner set..."));
			}

			
			return true;
		}
	}
	return false;
}


bool FClientAccelerateMotorStateManager::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{		
		FWorldContext serverContext = GEditor->GetWorldContexts()[1];//0 is editor, 1 is server, 2->N is clients
		if (serverContext.World()->GetNumPlayerControllers() == clientQuantity)
		{
			FWorldContext clientContext = GEditor->GetWorldContexts()[2];//0 is editor, 1 is server, 2->N is clients
			UE_LOG(LogTemp, Log, TEXT("retrieving motor state manager..."));
			AMotorStateManager* testClientManager = Cast<AMotorStateManager, AActor>(UGameplayStatics::GetActorOfClass(clientContext.World(), AMotorStateManager::StaticClass()));
			if (testClientManager)
			{
				UE_LOG(LogTemp, Log, TEXT("accelerating motor state manager..."));
				testClientManager->accelerate();
				return true;
			}
		}
	}
	return false;
}


bool FClientBrakeMotorStateManager::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{		
		FWorldContext serverContext = GEditor->GetWorldContexts()[1];//0 is editor, 1 is server, 2->N is clients
		if (serverContext.World()->GetNumPlayerControllers() == clientQuantity)
		{
			FWorldContext clientContext = GEditor->GetWorldContexts()[2];//0 is editor, 1 is server, 2->N is clients
			UE_LOG(LogTemp, Log, TEXT("retrieving motor state manager..."));
			AMotorStateManager* testClientManager = Cast<AMotorStateManager, AActor>(UGameplayStatics::GetActorOfClass(clientContext.World(), AMotorStateManager::StaticClass()));
			if (testClientManager)
			{
				UE_LOG(LogTemp, Log, TEXT("reversing motor state manager..."));
				testClientManager->brake();
				return true;
			}
		}
	}
	return false;
}









//Test check commands:


bool FCheckMotorStateManagerDefaultState::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			test->TestTrue(TEXT("The default state should be NeutralMotorState"), testManager->currentState()->GetClass() == ANeutralMotorState::StaticClass() );
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;	
		}
	}
	return false;
}


bool FCheckMotorStateManagerStateChangesToAccelerating::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			test->TestTrue(TEXT("After accelerate, the motorState should be Accelerating"), testManager->currentState()->GetClass() == AAcceleratingMotorState::StaticClass() );
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;	
		}
	}
	return false;
}


bool FCheckMotorStateManagerStateChangesToReversing::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			test->TestTrue(TEXT("After brake, the motorState should be Reversing"), testManager->currentState()->GetClass() == AReversingMotorState::StaticClass() );
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;	
		}
	}
	return false;
}


bool FCheckMotorStateManagerStateChangesToNeutral::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			test->TestTrue(TEXT("After neutralize, the motorState should be Neutral"), testManager->currentState()->GetClass() == ANeutralMotorState::StaticClass() );
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;	
		}
	}
	return false;
}


bool FCheckMotorStateManagerAccelerateKeepsStateIfAccelerating::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			testManager->accelerate();
			AMotorState* currentState = testManager->currentState();
			bool statesMatch = previousState == currentState;
			
			if(statesMatch)
			{
				test->TestTrue(TEXT("Should keep its state if accelerate when already Accelerating"), statesMatch );
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;	
			}
			previousState = currentState;

			++tickCount;
			if(tickCount > tickLimit)
			{
				test->TestTrue(TEXT("Should keep its state if accelerate when already Accelerating"), statesMatch );
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckMotorStateManagerBrakeKeepsStateIfReversing::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			testManager->brake();
			AMotorState* currentState = testManager->currentState();
			bool statesMatch = previousState == currentState;
			
			if(statesMatch)
			{
				test->TestTrue(TEXT("Should keep its state if brake when already Reversing"), statesMatch );
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;	
			}
			previousState = currentState;
			
			++tickCount;
			if(tickCount > tickLimit)
			{
				test->TestTrue(TEXT("Should keep its state if brake when already Reversing"), statesMatch );
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckMotorStateManagerNeutralizeKeepsStateIfNeutral::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			testManager->neutralize();
			AMotorState* currentState = testManager->currentState();
			bool statesMatch = previousState == currentState;
			
			if(statesMatch)
			{
				test->TestTrue(TEXT("Should keep its state if neutralize when already Neutral"), statesMatch );
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;	
			}
			previousState = currentState;
			
			++tickCount;
			if(tickCount > tickLimit)
			{
				test->TestTrue(TEXT("Should keep its state if neutralize when already Neutral"), statesMatch );
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckMotorStateManagerLeavesOneStateInWorld::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			int statesInWorld = sessionUtilities.retrieveFromPIEAllInstancesOf<AMotorState>().Num();	
			test->TestTrue(TEXT("After accelerating, braking and/or neutralizing, only one motor state remains in the world"), statesInWorld == 1 );
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;	
		}
	}
	return false;	
}


bool FCheckMotorStateManagerServerAndClientAcceleratingState::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		FWorldContext serverContext = GEditor->GetWorldContexts()[1];
		AMotorStateManagerMOCK* testServerManager = Cast<AMotorStateManagerMOCK, AActor>(UGameplayStatics::GetActorOfClass(serverContext.World(), AMotorStateManagerMOCK::StaticClass()));
		if(serverContext.World()->GetNumPlayerControllers() == clientQuantity && testServerManager)
		{
			FWorldContext clientContext = GEditor->GetWorldContexts()[2];//0 is editor, 1 is server, 2->N is clients
			UE_LOG(LogTemp, Log, TEXT("retrieving motor state manager for checking..."));
			AMotorStateManagerMOCK* testClientManager = Cast<AMotorStateManagerMOCK, AActor>(UGameplayStatics::GetActorOfClass(clientContext.World(), AMotorStateManagerMOCK::StaticClass()));

			bool bothAccelerating = false;
			if(testClientManager)
			{
				bool clientStateIsAccelerating = testClientManager->currentState()->GetClass() == AAcceleratingMotorState::StaticClass();
				bool serverStateIsAccelerating = testServerManager->currentState()->GetClass() == AAcceleratingMotorState::StaticClass();
				bothAccelerating = serverStateIsAccelerating && clientStateIsAccelerating;
			}

			if(bothAccelerating)
			{
				test->TestTrue(TEXT("The server should replicate its state when calling accelerate."), bothAccelerating);
				for(auto context : GEditor->GetWorldContexts())
				{
					context.World()->bDebugFrameStepExecution = true;
				}
				return true;
			}

			++tickCount;
			if(tickCount > tickLimit)
			{
				test->TestTrue(TEXT("The server should replicate its state when calling accelerate."), bothAccelerating);
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


bool FCheckMotorStateManagerServerAndClientReversingState::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		FWorldContext serverContext = GEditor->GetWorldContexts()[1];
		AMotorStateManagerMOCK* testServerManager = Cast<AMotorStateManagerMOCK, AActor>(UGameplayStatics::GetActorOfClass(serverContext.World(), AMotorStateManagerMOCK::StaticClass()));
		if(serverContext.World()->GetNumPlayerControllers() == clientQuantity && testServerManager)
		{
			FWorldContext clientContext = GEditor->GetWorldContexts()[2];//0 is editor, 1 is server, 2->N is clients
			UE_LOG(LogTemp, Log, TEXT("retrieving motor state manager for checking..."));
			AMotorStateManagerMOCK* testClientManager = Cast<AMotorStateManagerMOCK, AActor>(UGameplayStatics::GetActorOfClass(clientContext.World(), AMotorStateManagerMOCK::StaticClass()));

			bool bothReversing = false;
			if(testClientManager)
			{
				bool clientStateIsReversing = testClientManager->currentState()->GetClass() == AReversingMotorState::StaticClass();
				bool serverStateIsReversing = testServerManager->currentState()->GetClass() == AReversingMotorState::StaticClass();
				bothReversing = serverStateIsReversing && clientStateIsReversing;
			}

			if(bothReversing)
			{
				test->TestTrue(TEXT("The server should replicate its state when calling brake."), bothReversing);
				for(auto context : GEditor->GetWorldContexts())
				{
					context.World()->bDebugFrameStepExecution = true;
				}
				return true;
			}

			++tickCount;
			if(tickCount > tickLimit)
			{
				test->TestTrue(TEXT("The server should replicate its state when calling brake."), bothReversing);
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
