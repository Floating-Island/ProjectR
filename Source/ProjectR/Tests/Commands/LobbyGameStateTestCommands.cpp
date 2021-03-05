// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "LobbyGameStateTestCommands.h"
#include "GameState/LobbyGameState.h"
#include "../Utilities/PIESessionUtilities.h"

//Test preparation commands:



//Test check commands:


bool FCheckLobbyGameStateExistsInLobby::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		ALobbyGameState* testLobby = sessionUtilities.retrieveFromPIEAnInstanceOf<ALobbyGameState>();

		bool lobbyGameStatePresent = testLobby != nullptr;
		
		if(lobbyGameStatePresent)
		{
			test->TestTrue(test->conditionMessage(), lobbyGameStatePresent);
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
		return test->manageTickCountTowardsLimit();
	}
	return false;
}


#endif //WITH_DEV_AUTOMATION_TESTS
