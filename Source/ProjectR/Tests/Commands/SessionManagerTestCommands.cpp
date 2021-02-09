// Fill out your copyright notice in the Description page of Project Settings.


#include "../Utilities/NetworkedPIESessionUtilities.h"
#if WITH_DEV_AUTOMATION_TESTS

#include "SessionManagerTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "../Utilities/ObjectContainerActor.h"
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


bool FServerCreateLANSession::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		FWorldContext serverContext = NetworkedPIESessionUtilities::retrieveServerWorldContext(clientQuantity);
		UWorld* serverWorld = serverContext.World();

		if(serverWorld)
		{
			AObjectContainerActor* testContainer = Cast<AObjectContainerActor, AActor>(UGameplayStatics::GetActorOfClass(serverWorld, AObjectContainerActor::StaticClass()));
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
		
	}
	return false;
}


bool FClientSpawnSessionManager::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		FWorldContext clientContext = NetworkedPIESessionUtilities::retrieveClientWorldContextSafely(clientQuantity);
		UWorld* clientWorld = clientContext.World();

		if(clientWorld)
		{
			return clientWorld->SpawnActor(AObjectContainerActor::StaticClass()) ? true : false;
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


bool FUSessionManagerCheckClientFindsAtLeastOneLANSession::Update()
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

				AObjectContainerActor* testContainer = Cast<AObjectContainerActor, AActor>(UGameplayStatics::GetActorOfClass(clientWorld, AObjectContainerActor::StaticClass()));

				if(testContainer)
				{
					testContainer->storeObjectOfType<USessionManager>();
					USessionManager* testManager = Cast<USessionManager, UObject>(testContainer->retrieveStoredObject());
					testManager->searchLANSessions();
					if(testManager)
					{
						bool hasFoundSessions = testManager->sessionSearchResults().Num() > 0;
						test->TestTrue("After a session is created, searchLANSessions should generate search results with at least one entry.", hasFoundSessions);
						
						for(auto context : GEditor->GetWorldContexts())
						{
							context.World()->bDebugFrameStepExecution = true;
						}
						return true;
					}
				}
				++tickCount;
				if(tickCount > tickLimit)
				{
					test->TestTrue("After a session is created, searchLANSessions should generate search results with at least one entry.", tickCount > tickLimit);
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







#endif //WITH_DEV_AUTOMATION_TESTS
