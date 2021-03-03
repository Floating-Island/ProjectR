// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "RaceResultsUITestCommands.h"
#include "UI/RaceResultsUI.h"
#include "../Utilities/BlueprintWidgetContainerPawn.h"
#include "../Utilities/PIESessionUtilities.h"
#include "GameState/ProjectRGameState.h"

//Test preparation commands:



//Test check commands:


bool FCheckRaceResultsInfoBoxQuantitySameAsPlayerStates::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ABlueprintWidgetContainerPawn* testContainer = sessionUtilities.retrieveFromPIEAnInstanceOf<ABlueprintWidgetContainerPawn>();
		
		if(testContainer)
		{
			URaceResultsUI* testResults = Cast<URaceResultsUI, UUserWidget>(testContainer->retrieveWidget());
			AProjectRGameState* testGameState = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRGameState>();

			bool QuantitiesCoincident = testResults->rowsQuantity() == testGameState->PlayerArray.Num();
			if(QuantitiesCoincident)
			{
				test->TestTrue(test->conditionMessage(), QuantitiesCoincident);
				return true;
			}
			return test->manageTickCountTowardsLimit();
		}
	}
	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
