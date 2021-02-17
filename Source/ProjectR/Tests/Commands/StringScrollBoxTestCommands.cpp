// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "StringScrollBoxTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "UI/StringButtonScrollBox.h"
#include "../Utilities/BlueprintWidgetContainerPawn.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/StringHolderButton.h"

//Test preparation commands:





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


bool FCheckAStringScrollBoxChildClicked::Update()
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

			TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
			UWidgetBlueprintLibrary::GetAllWidgetsOfClass(sessionUtilities.currentPIEWorld(),retrievedWidgets, UStringHolderButton::StaticClass());

			if(retrievedWidgets.Num() > 0)
			{
				if(aButtonHolder == nullptr)
				{
					aButtonHolder = Cast<UStringHolderButton, UUserWidget>(retrievedWidgets.Pop());
				}

				FVector2D buttonCoordinates = aButtonHolder->buttonCoordinates();
				sessionUtilities.processEditorClick(buttonCoordinates);
				
				bool textsMatch = aButtonHolder->storedString().Contains(testScroll->selectedString());
				
				if(textsMatch)
				{
					test->TestTrue(test->conditionMessage(), textsMatch);
					sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
					return true;
				}
				return test->manageTickCountTowardsLimit();
			}
		}
	}
	return false;
}




#endif //WITH_DEV_AUTOMATION_TESTS
