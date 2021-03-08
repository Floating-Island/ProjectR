// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "StringHolderButtonTestCommands.h"
#include "../../Utilities/PIESessionUtilities.h"
#include "UI/StringHolderButton.h"
#include "../../Utilities/BlueprintWidgetContainerPawn.h"

//Test preparation commands:





//Test check commands:


bool FCheckAStringHolderButtonStoresAndRetrievesString::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ABlueprintWidgetContainerPawn* testContainer = sessionUtilities.retrieveFromPIEAnInstanceOf<ABlueprintWidgetContainerPawn>();
		
		if(testContainer)
		{
			UStringHolderButton* testButton = Cast<UStringHolderButton, UUserWidget>(testContainer->retrieveWidget());
			FString testString = FString("I'm going into the string holder button.");

			testButton->store(testString);
			bool stringsCoincident = testButton->storedString().Contains(testString);
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
