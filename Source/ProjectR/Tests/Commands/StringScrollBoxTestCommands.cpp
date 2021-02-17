// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "StringScrollBoxTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "GameFramework/GameModeBase.h"
#include "UI/StringButtonScrollBox.h"
#include "../Utilities/BlueprintWidgetContainerPawn.h"

//Test preparation commands:

bool FSpawnGameModeDefaultPawn::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AGameModeBase* pieGameMode = sessionUtilities.currentPIEWorld()->GetAuthGameMode();
		APlayerController* pieController = sessionUtilities.currentPIEWorld()->GetFirstPlayerController();

		pieGameMode->SpawnDefaultPawnAtTransform(pieController, FTransform());
		return true;
	}
	return false;
}



//Test check commands:


bool FCheckAStringScrollBoxPopulateBoxNumberOfChilds::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ABlueprintWidgetContainerPawn* testContainer = sessionUtilities.retrieveFromPIEAnInstanceOf<ABlueprintWidgetContainerPawn>();
		
		if(testContainer)
		{
			UStringButtonScrollBox* testScroll = Cast<UStringButtonScrollBox, UUserWidget>(testContainer->retrieveWidget());
			TArray<FString> testStrings = TArray<FString>();
			testStrings.Add(FString("I'm "));
			testStrings.Add(FString("a "));
			testStrings.Add(FString("string."));

			testScroll->populateBox(testStrings);
			bool numbersCoincident = testScroll->stringButtonsQuantity() == testStrings.Num();
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
