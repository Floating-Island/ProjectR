// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "SessionManagerTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "../Utilities/ObjectContainerActor.h"
#include "../Utilities/NetworkedPIESessionUtilities.h"
#include "Session/SessionManager.h"

//Test preparation commands:

bool FUSessionManagerCreateSession::Update()
{
	if (GEditor->IsPlayingSessionInEditor())//if not, everything would be made while the map is loading and the PIE is in progress.
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		AObjectContainerActor* testContainer = sessionUtilities.retrieveFromPIEAnInstanceOf<AObjectContainerActor>();

		if(testContainer)
		{
			testContainer->storeObjectOfType<USessionManager>();
			USessionManager* testManager = Cast<USessionManager, UObject>(testContainer->retrieveStoredObject());
			if(testManager)
			{
				testManager->createLANSession();
				return true;
			}
		}
	}
	return false;
}


bool FClientSpawnSessionManagerAndCreateSession::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		FWorldContext clientContext = NetworkedPIESessionUtilities::retrieveClientWorldContextSafely(clientQuantity);
		UWorld* clientWorld = clientContext.World();

		if(clientWorld)
		{
			AObjectContainerActor* testContainer = Cast<AObjectContainerActor, AActor>(clientWorld->SpawnActor(AObjectContainerActor::StaticClass()));
			UE_LOG(LogTemp, Log, TEXT("creating container..."));
			if(testContainer)
			{
				testContainer->storeObjectOfType<USessionManager>();
				USessionManager* testManager = Cast<USessionManager, UObject>(testContainer->retrieveStoredObject());
				UE_LOG(LogTemp, Log, TEXT("creating session manager..."));
				if(testManager)
				{
					UE_LOG(LogTemp, Log, TEXT("creating session..."));
					testManager->createLANSession();
					return true;
				}
			}
		}
		
	}
	return false;
}













//Test check commands:



bool FUSessionManagerCreateAndCheckSessionCreation::Update()
{
	if (GEditor->IsPlayingSessionInEditor())//if not, everything would be made while the map is loading and the PIE is in progress.
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		AObjectContainerActor* testContainer = sessionUtilities.retrieveFromPIEAnInstanceOf<AObjectContainerActor>();

		if(testContainer)
		{
			testContainer->storeObjectOfType<USessionManager>();
			USessionManager* testManager = Cast<USessionManager, UObject>(testContainer->retrieveStoredObject());
			if(testManager)
			{
				test->TestTrue("createLANSession should start the asynchronous creation of a LAN session", testManager->createLANSession());

				testManager->destroyCurrentSession();
				
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FUSessionManagerCheckTravelToLobby::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		
		UE_LOG(LogTemp, Log, TEXT("current PIE world: %s."), *sessionUtilities.currentPIEWorld()->GetMapName());
		bool isInAnotherWorld = !sessionUtilities.currentPIEWorld()->GetMapName().Contains("voidWorld");

		if (isInAnotherWorld)
		{
			test->TestTrue(TEXT("The session manager should travel to the lobby when the session starts."), isInAnotherWorld);

			AObjectContainerActor* objectContainer = sessionUtilities.spawnInPIEAnInstanceOf<AObjectContainerActor>();
			objectContainer->storeObjectOfType<USessionManager>();
			USessionManager* testManager = Cast<USessionManager, UObject>(objectContainer->retrieveStoredObject());
			testManager->destroyCurrentSession();
			
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}

		++tickCount;
		if (tickCount > tickLimit)
		{
			test->TestTrue(TEXT("The session manager should travel to the lobby when the session starts."), isInAnotherWorld);
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}


bool FUSessionManagerCheckSessionDestructionStarting::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		
		UE_LOG(LogTemp, Log, TEXT("current PIE world: %s."), *sessionUtilities.currentPIEWorld()->GetMapName());
		bool isInAnotherWorld = !sessionUtilities.currentPIEWorld()->GetMapName().Contains("voidWorld");

		if (isInAnotherWorld)
		{
			AObjectContainerActor* objectContainer = sessionUtilities.spawnInPIEAnInstanceOf<AObjectContainerActor>();

			objectContainer->storeObjectOfType<USessionManager>();
			USessionManager* testManager = Cast<USessionManager, UObject>(objectContainer->retrieveStoredObject());
			
			test->TestTrue(TEXT("The session manager should start session destruction when calling destroyCurrentSession."), testManager->destroyCurrentSession());
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;

		}
		++tickCount;
		if (tickCount > tickLimit)
		{
			test->TestTrue(TEXT("The session manager should start session destruction when calling destroyCurrentSession."), isInAnotherWorld);
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}


bool FUSessionManagerCheckSessionSearching::Update()
{
	if (GEditor->IsPlayingSessionInEditor())//if not, everything would be made while the map is loading and the PIE is in progress.
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		AObjectContainerActor* testContainer = sessionUtilities.retrieveFromPIEAnInstanceOf<AObjectContainerActor>();

		if(testContainer)
		{
			testContainer->storeObjectOfType<USessionManager>();
			USessionManager* testManager = Cast<USessionManager, UObject>(testContainer->retrieveStoredObject());
			if(testManager)
			{
				test->TestTrue("searchLANSessions should start the asynchronous search of LAN sessions", testManager->searchLANSessions());
				
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}







#endif //WITH_DEV_AUTOMATION_TESTS
