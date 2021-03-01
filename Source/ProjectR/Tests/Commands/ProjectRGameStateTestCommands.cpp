// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "ProjectRGameStateTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "GameState/ProjectRGameState.h"
#include "../../Public/UI/AnnouncerUI.h"
#include "../Utilities/BlueprintWidgetContainerPawn.h"

//Test preparation commands:






//Test check commands:



bool FCheckPlayerStateUpdatesRacePlayerUICurrentLap::Update()
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

		FString stateAnnouncerText = testState->announcerText();
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







#endif //WITH_DEV_AUTOMATION_TESTS
