// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "RacePlayerUITestCommands.h"
#include "../Utilities/BlueprintWidgetContainerPawn.h"
#include "../Utilities/PIESessionUtilities.h"
#include "UI/RacePlayerUI.h"

//Test preparation commands:



//Test check commands:


bool FCheckARacePlayerUIChangesTotalLapsText::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ABlueprintWidgetContainerPawn* testContainer = sessionUtilities.retrieveFromPIEAnInstanceOf<ABlueprintWidgetContainerPawn>();
		
		if(testContainer)
		{
			URacePlayerUI* testUI = Cast<URacePlayerUI, UUserWidget>(testContainer->retrieveWidget());
			int desiredTextValue = 5;

			testUI->setTotalLapsTo(desiredTextValue);
			bool valuesCoincident = testUI->totalLaps() == desiredTextValue;
			if(valuesCoincident)
			{
				test->TestTrue(test->conditionMessage(), valuesCoincident);
				return true;
			}
			return test->manageTickCountTowardsLimit();
		}
	}
	return false;
}


bool FCheckARacePlayerUIChangesTotalLapsTextOnce::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ABlueprintWidgetContainerPawn* testContainer = sessionUtilities.retrieveFromPIEAnInstanceOf<ABlueprintWidgetContainerPawn>();
		
		if(testContainer)
		{
			URacePlayerUI* testUI = Cast<URacePlayerUI, UUserWidget>(testContainer->retrieveWidget());
			int desiredFirstTextValue = 5;

			int desiredSecondTextValue = 7;

			testUI->setTotalLapsTo(desiredFirstTextValue);
			testUI->setTotalLapsTo(desiredSecondTextValue);


			bool firstValuesSetCoincident = testUI->totalLaps() == desiredFirstTextValue;
			bool secondValuesSetDiffer = testUI->totalLaps() != desiredSecondTextValue;

			bool setsValuesOnce = firstValuesSetCoincident && secondValuesSetDiffer;
			
			if(setsValuesOnce)
			{
				test->TestTrue(test->conditionMessage(), setsValuesOnce);
				return true;
			}
			return test->manageTickCountTowardsLimit();
		}
	}
	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
