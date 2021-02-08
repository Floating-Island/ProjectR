// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "SessionManagerTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "../Utilities/ObjectContainerActor.h"
#include "Session/SessionManager.h"

//Test preparation commands:



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
			test->TestTrue("createLANSession should start the asynchronous creation of a LAN session", testManager->createLANSession());

			return true;
		}
	}
	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
