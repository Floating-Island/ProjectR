// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "RaceBeginningStageTestCommands.h"
#include "GameMode/RaceStages/RaceBeginningStage.h"
#include "../Mocks/RaceBeginningStageMOCK.h"
#include "GameMode/RaceStages/RaceRunningStage.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/AnnouncerUI.h"
#include "GameState/ProjectRGameState.h"


#include "Tests/AutomationEditorCommon.h"
#include "../Utilities/PIESessionUtilities.h"

//Test preparation commands:

bool FSpawnARaceBeginningMOCK::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	ARaceBeginningStageMOCK* testBeginning = sessionUtilities.spawnInPIEAnInstanceOf<ARaceBeginningStageMOCK>();

	testBeginning->start();
	return true;
}


bool FSpawnARaceBeginningCallCountdownStart::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	ARaceBeginningStage* testBeginning = sessionUtilities.spawnInPIEAnInstanceOf<ARaceBeginningStage>();

	testBeginning->nextStage();
	return true;
}









//Test check commands:

bool FCheckTimerActive::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();

	ARaceBeginningStageMOCK* testBeginning = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceBeginningStageMOCK>();
	if (testBeginning)
	{
		test->TestTrue(TEXT("Race beginning stage should have its timer active at start."), testBeginning->hasTimerActive());
		testWorld->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckRunningStageSpawned::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();

	ARaceBeginningStage* testBeginning = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceBeginningStage>();
	if (testBeginning)
	{
		ARaceRunningStage* testRunning = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceRunningStage>();
		
		test->TestNotNull(TEXT("Race beginning next stage should spawn a race running stage."), testRunning);
		testWorld->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckRaceBeginningStageLoadsAnnouncerUIs::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();

		ARaceBeginningStage* testBeginning = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceBeginningStage>();
		if (testBeginning)
		{
			TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
			UWidgetBlueprintLibrary::GetAllWidgetsOfClass(testWorld,retrievedWidgets, UAnnouncerUI::StaticClass(), false);

			int numberOfAnnouncers = retrievedWidgets.Num();
			UE_LOG(LogTemp, Log, TEXT("announcer UI quantity: %d."), numberOfAnnouncers);

			int numberOfControllers = testWorld->GetNumPlayerControllers();
			UE_LOG(LogTemp, Log, TEXT("Controllers quantity: %d."), numberOfControllers);

			bool quantitiesMatch = numberOfControllers == numberOfAnnouncers;

			if(quantitiesMatch)
			{
				test->TestTrue(test->conditionMessage(), quantitiesMatch);
				for(auto context : GEditor->GetWorldContexts())
				{
					context.World()->bDebugFrameStepExecution = true;
				}
				return true;
			}
			return test->manageTickCountTowardsLimit();
		}
	}
	return false;
}


bool FCheckRaceBeginningStageCountdownToStartModifiesAnnouncerText::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();

		ARaceBeginningStageMOCK* testBeginning = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceBeginningStageMOCK>();
		if (testBeginning)
		{
			testBeginning->loadAnnouncers();

			int arbitraryNumber = 5;
			UE_LOG(LogTemp, Log, TEXT("desired announcer number: %d."), arbitraryNumber);

			testBeginning->countdownToStart(arbitraryNumber);

			AProjectRGameState* testState = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRGameState>();

			int announcerToNumber = FCString::Atoi(*testState->announcerDisplayText());
			

			bool quantitiesMatch = arbitraryNumber == announcerToNumber;

			if(quantitiesMatch)
			{
				test->TestTrue(test->conditionMessage(), quantitiesMatch);
				for(auto context : GEditor->GetWorldContexts())
				{
					context.World()->bDebugFrameStepExecution = true;
				}
				return true;
			}
			return test->manageTickCountTowardsLimit();
		}
	}
	return false;
}




#endif //WITH_DEV_AUTOMATION_TESTS
