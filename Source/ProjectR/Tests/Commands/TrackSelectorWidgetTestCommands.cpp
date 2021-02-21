// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/UI/StringHolderButton.h"
#include "../Utilities/BlueprintWidgetContainerPawn.h"
#include "../Utilities/PIESessionUtilities.h"
#if WITH_DEV_AUTOMATION_TESTS

#include "TrackSelectorWidgetTestCommands.h"

//Test preparation commands:



//Test check commands:


bool FCheckTrackSelectorCreatesButtonsAsMapsFound::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ABlueprintWidgetContainerPawn* testContainer = sessionUtilities.retrieveFromPIEAnInstanceOf<ABlueprintWidgetContainerPawn>();
		
		if(testContainer)
		{
			UTrackSelectorWidget* testSelector = Cast<UTrackSelectorWidget, UUserWidget>(testContainer->retrieveWidget());

			TArray<UStringHolderButton*> buttonsMade = TArray<UStringHolderButton*>();
			buttonsMade = sessionUtilities.retrieveFromPIEAllInstancesOf<UStringHolderButton>();
			
			TArray<FString> mapsFound = TArray<FString>();
			mapsFound = testSelector->mapsCollected();
			
			bool numbersCoincident = buttonsMade.Num() == mapsFound.Num();
			if(numbersCoincident)
			{
				test->TestTrue(test->conditionMessage(), numbersCoincident);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
			return test->manageTickCountTowardsLimit();
		}
	}
	return false;
}




#endif //WITH_DEV_AUTOMATION_TESTS
