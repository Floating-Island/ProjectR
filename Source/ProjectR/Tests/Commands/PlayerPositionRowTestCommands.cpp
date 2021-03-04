// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "PlayerPositionRowTestCommands.h"
#include "UI/PlayerPositionRow.h"
#include "../Utilities/BlueprintWidgetContainerPawn.h"
#include "../Utilities/PIESessionUtilities.h"

//Test preparation commands:



//Test check commands:


bool FCheckPlayerPositionRowUpdatesWithGivenInfo::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ABlueprintWidgetContainerPawn* testContainer = sessionUtilities.retrieveFromPIEAnInstanceOf<ABlueprintWidgetContainerPawn>();
		
		if(testContainer)
		{
			UPlayerPositionRow* testRow = Cast<UPlayerPositionRow, UUserWidget>(testContainer->retrieveWidget());
			FString testPlayerName = FString("I'm you.");
			FString testPosition = FString("3");

			testRow->updateInfoWith(testPlayerName, testPosition);
			bool stringsCoincident = testRow->playerName() == testPlayerName && testRow->position() == testPosition;
			if(stringsCoincident)
			{
				test->TestTrue(test->conditionMessage(), stringsCoincident);
				return true;
			}
			return test->manageTickCountTowardsLimit();
		}
	}
	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
