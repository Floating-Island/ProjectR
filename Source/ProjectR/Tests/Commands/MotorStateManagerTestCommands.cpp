// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "MotorStateManagerTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "../Utilities/NetworkedPIESessionUtilities.h"

#include "../Mocks/MotorStateManagerMOCK.h"
#include "Jet/MotorStates/NeutralMotorState.h"
#include "Jet/MotorStates/AcceleratingMotorState.h"
#include "Jet/MotorStates/ReversingMotorState.h"
#include "Jet/MotorStates/MixedMotorState.h"


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


//bool FSpawnAMotorStateManagerBrakeAccelerateAndNeutralizeIt::Update()//relying on the garbage collector to destroy the replaced objects
//{
//	if(GEditor->IsPlayingSessionInEditor())
//	{
//		PIESessionUtilities sessionUtilities = PIESessionUtilities();
//		AMotorStateManagerMOCK* testManager = sessionUtilities.spawnInPIEAnInstanceOf<AMotorStateManagerMOCK>();
//
//		testManager->brake();
//		testManager->accelerate();
//		testManager->neutralize();
//		
//		return true;
//	}
//
//	return false;
//}


bool FClientAccelerateMotorStateManager::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{		
		FWorldContext serverContext = NetworkedPIESessionUtilities::retrieveServerWorldContext(clientQuantity);
		UWorld* serverWorld = serverContext.World();

		if(serverWorld)
		{
			FWorldContext clientContext = NetworkedPIESessionUtilities::retrieveClientWorldContext();
			UWorld* clientWorld = clientContext.World();

			if(clientWorld)
			{
				UE_LOG(LogTemp, Log, TEXT("retrieving motor state manager..."));
				AMotorStateManager* testClientManager = Cast<AMotorStateManager, AActor>(UGameplayStatics::GetActorOfClass(clientWorld, AMotorStateManager::StaticClass()));

				if (testClientManager)
				{
					UE_LOG(LogTemp, Log, TEXT("accelerating motor state manager..."));
					testClientManager->accelerate();
					return true;
				}
			}
		}
	}
	return false;
}


bool FClientBrakeMotorStateManager::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{		
		FWorldContext serverContext = NetworkedPIESessionUtilities::retrieveServerWorldContext(clientQuantity);
		UWorld* serverWorld = serverContext.World();

		if(serverWorld)
		{
			FWorldContext clientContext = NetworkedPIESessionUtilities::retrieveClientWorldContext();
			UWorld* clientWorld = clientContext.World();

			if(clientWorld)
			{
				UE_LOG(LogTemp, Log, TEXT("retrieving motor state manager..."));
				AMotorStateManager* testClientManager = Cast<AMotorStateManager, AActor>(UGameplayStatics::GetActorOfClass(clientWorld, AMotorStateManager::StaticClass()));

				if (testClientManager)
				{
					UE_LOG(LogTemp, Log, TEXT("reversing motor state manager..."));
					testClientManager->brake();
					return true;
				}
			}
		}
	}
	return false;
}


bool FClientNeutralizeMotorStateManager::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{		
		FWorldContext serverContext = NetworkedPIESessionUtilities::retrieveServerWorldContext(clientQuantity);
		UWorld* serverWorld = serverContext.World();

		if(serverWorld)
		{
			FWorldContext clientContext = NetworkedPIESessionUtilities::retrieveClientWorldContext();
			UWorld* clientWorld = clientContext.World();

			if(clientWorld)
			{
				UE_LOG(LogTemp, Log, TEXT("retrieving motor state manager..."));
				AMotorStateManager* testClientManager = Cast<AMotorStateManager, AActor>(UGameplayStatics::GetActorOfClass(clientWorld, AMotorStateManager::StaticClass()));

				if (testClientManager)
				{
					UE_LOG(LogTemp, Log, TEXT("neutralizing motor state manager..."));
					testClientManager->neutralize();
					return true;
				}
			}
		}
	}
	return false;
}


bool FSpawnAMotorStateManagerAndMixIt::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.spawnInPIEAnInstanceOf<AMotorStateManagerMOCK>();

		testManager->mix();
		
		return true;
	}

	return false;
}


bool FClientMixMotorStateManager::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{		
		FWorldContext serverContext = NetworkedPIESessionUtilities::retrieveServerWorldContext(clientQuantity);
		UWorld* serverWorld = serverContext.World();

		if(serverWorld)
		{
			FWorldContext clientContext = NetworkedPIESessionUtilities::retrieveClientWorldContext();
			UWorld* clientWorld = clientContext.World();

			if(clientWorld)
			{
				UE_LOG(LogTemp, Log, TEXT("retrieving motor state manager..."));
				AMotorStateManager* testClientManager = Cast<AMotorStateManager, AActor>(UGameplayStatics::GetActorOfClass(clientWorld, AMotorStateManager::StaticClass()));

				if (testClientManager)
				{
					UE_LOG(LogTemp, Log, TEXT("mixing motor state manager..."));
					testClientManager->mix();
					return true;
				}
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
			test->TestTrue(TEXT("The default state should be NeutralMotorState"), testManager->currentState()->GetClass() == UNeutralMotorState::StaticClass() );
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
			test->TestTrue(TEXT("After accelerate, the motorState should be Accelerating"), testManager->currentState()->GetClass() == UAcceleratingMotorState::StaticClass() );
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
			test->TestTrue(TEXT("After brake, the motorState should be Reversing"), testManager->currentState()->GetClass() == UReversingMotorState::StaticClass() );
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
			test->TestTrue(TEXT("After neutralize, the motorState should be Neutral"), testManager->currentState()->GetClass() == UNeutralMotorState::StaticClass() );
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
			UMotorState* currentState = testManager->currentState();
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
			UMotorState* currentState = testManager->currentState();
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
			UMotorState* currentState = testManager->currentState();
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


//bool FCheckMotorStateManagerLeavesOneStateInWorld::Update()//after changing the motor state to a uobject, I have to rely on the garbage collector to destroy them
//{
//	if(GEditor->IsPlayingSessionInEditor())
//	{
//		PIESessionUtilities sessionUtilities = PIESessionUtilities();
//		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
//		if(testManager)
//		{
//			int statesInWorld = sessionUtilities.retrieveFromPIEAllInstancesOf<UMotorState>().Num();	
//			test->TestTrue(TEXT("After accelerating, braking and/or neutralizing, only one motor state remains in the world"), statesInWorld == 1 );
//			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
//			return true;	
//		}
//	}
//	return false;	
//}


bool FCheckMotorStateManagerServerAndClientExpectedState::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		FWorldContext serverContext = NetworkedPIESessionUtilities::retrieveServerWorldContext(clientQuantity);
		UWorld* serverWorld = serverContext.World();

		if(serverWorld)
		{
			FWorldContext clientContext = NetworkedPIESessionUtilities::retrieveClientWorldContext();
			UWorld* clientWorld = clientContext.World();

			if(clientWorld)
			{
				UE_LOG(LogTemp, Log, TEXT("retrieving motor state manager for checking..."));
				AMotorStateManagerMOCK* testServerManager = Cast<AMotorStateManagerMOCK, AActor>(UGameplayStatics::GetActorOfClass(serverWorld, AMotorStateManagerMOCK::StaticClass()));
				AMotorStateManagerMOCK* testClientManager = Cast<AMotorStateManagerMOCK, AActor>(UGameplayStatics::GetActorOfClass(clientWorld, AMotorStateManagerMOCK::StaticClass()));
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
	}
	return false;
}


bool FCheckMotorStateManagerStateChangesToMixed::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			test->TestTrue(TEXT("After mix, the motorState should be Mixed"), testManager->currentState()->GetClass() == UMixedMotorState::StaticClass() );
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;	
		}
	}
	return false;
}


bool FCheckMotorStateManagerMixKeepsStateIfMixed::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			testManager->mix();
			UMotorState* currentState = testManager->currentState();
			bool statesMatch = previousState == currentState;
			
			if(statesMatch)
			{
				test->TestTrue(TEXT("Should keep its state if mix when already Mixed"), statesMatch );
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;	
			}
			previousState = currentState;

			++tickCount;
			if(tickCount > tickLimit)
			{
				test->TestTrue(TEXT("Should keep its state if mix when already Mixed"), statesMatch );
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}







#endif //WITH_DEV_AUTOMATION_TESTS
