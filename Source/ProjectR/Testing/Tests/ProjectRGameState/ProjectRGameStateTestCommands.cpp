// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "ProjectRGameStateTestCommands.h"
#include "../../Utilities/PIESessionUtilities.h"
#include "GameState/ProjectRGameState.h"
#include "UI/AnnouncerUI.h"
#include "../../Utilities/BlueprintWidgetContainerPawn.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "PlayerController/ProjectRPlayerController.h"
#include "../../Utilities/NetworkedPIESessionUtilities.h"

//Test preparation commands:






//Test check commands:



bool FCheckGameStateUpdatesAnnouncerUIDisplayText::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		
		ABlueprintWidgetContainerPawn* testContainer = sessionUtilities.retrieveFromPIEAnInstanceOf<ABlueprintWidgetContainerPawn>();
		if(testContainer == nullptr)
		{
			return false;
		}
		
		UAnnouncerUI* testAnnouncerUI = Cast<UAnnouncerUI, UUserWidget>(testContainer->retrieveWidget());
		if (testAnnouncerUI == nullptr)
		{
			return false;
		}
		
		AProjectRGameState* testState = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRGameState>();
		if(testState == nullptr)
		{
			sessionUtilities.spawnInPIEAnInstanceOf<AProjectRGameState>();
			return false;
		}

		testState->subscribeToAnnouncerUpdate(testAnnouncerUI);

		FString arbitraryAnnouncerText = FString("5");
		testState->updateAnnouncerWith(arbitraryAnnouncerText);

		FString stateAnnouncerText = testState->announcerDisplayText();
		UE_LOG(LogTemp, Log, TEXT("game state announcer text: %s."), *stateAnnouncerText);
		
		FString uiAssignedText = testAnnouncerUI->assignedText();
		UE_LOG(LogTemp, Log, TEXT("announcer UI text: %s."), *uiAssignedText);

		bool textsMatch = stateAnnouncerText == uiAssignedText;

		if(textsMatch)
		{
			test->TestTrue(test->conditionMessage(), textsMatch);
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
		return test->manageTickCountTowardsLimit();
	}
	return false;
}


bool FCheckServerGameStateUpdatesClientAnnouncerUIDisplayText::Update()
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
				UE_LOG(LogTemp, Log, TEXT("making controllers load the announcer UI..."));
				for (auto iterator = serverWorld->GetPlayerControllerIterator(); iterator; ++iterator)
				{
					AProjectRPlayerController* controller = Cast<AProjectRPlayerController, APlayerController>(iterator->Get());
					controller->loadAnnouncerUI();
				}
				
				AProjectRGameState* testState = Cast<AProjectRGameState, AGameStateBase>(serverWorld->GetGameState());
				FString arbitraryAnnouncerText = FString("5");
				UE_LOG(LogTemp, Log, TEXT("desired announcer text: %s."), *arbitraryAnnouncerText);
				testState->updateAnnouncerWith(arbitraryAnnouncerText);
				
				
				TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
				UWidgetBlueprintLibrary::GetAllWidgetsOfClass(clientWorld,retrievedWidgets, UAnnouncerUI::StaticClass(), false);

				if(retrievedWidgets.Num() == 0)
				{
					UE_LOG(LogTemp, Log, TEXT("couldn't find announcerUIs..."));
					return false;
				}
				
				UAnnouncerUI* testAnnouncerUI = Cast<UAnnouncerUI, UUserWidget>(retrievedWidgets.Pop());
				FString uiText = testAnnouncerUI->assignedText();
				UE_LOG(LogTemp, Log, TEXT("announcer UI display text: %s."), *uiText);

				bool textsMatch = arbitraryAnnouncerText == uiText;

				if(textsMatch)
				{
					test->TestTrue(test->conditionMessage(), textsMatch);
					for(auto context : GEditor->GetWorldContexts())
					{
						context.World()->bDebugFrameStepExecution = true;
					}
					return true;
				}
				return test->manageTickCountTowardsLimit();
			}
		}
	}
	return false;
}








#endif //WITH_DEV_AUTOMATION_TESTS
