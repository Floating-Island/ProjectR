// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "RaceRunningStageTestCommands.h"
#include "GameMode/RaceStages/RaceRunningStage.h"
#include "GameMode/RaceStages/RaceEndedStage.h"
#include "GameMode/RaceStages/RacePreparationStage.h"
#include "Jet/Jet.h"

#include "../Mocks/RaceGameModeMOCK.h"
#include "../Mocks/RaceRunningStageMOCK.h"
#include "../Utilities/PIESessionUtilities.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "PlayerController/ProjectRPlayerController.h"
#include "UI/AnnouncerUI.h"

//Test preparation commands:

bool FSpawnARaceRunningCallNextStage::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	ARaceRunningStage* testRunning = sessionUtilities.spawnInPIEAnInstanceOf<ARaceRunningStage>();

	testRunning->nextStage();
	return true;
}


bool FSpawnARaceRunningAndStart::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	sessionUtilities.spawnLocalPlayer();
	ARacePreparationStage* testPreparation = sessionUtilities.spawnInPIEAnInstanceOf<ARacePreparationStage>();
	testPreparation->start();
	testPreparation->Destroy();
	
	ARaceRunningStage* testRunning = sessionUtilities.spawnInPIEAnInstanceOf<ARaceRunningStage>();
	sessionUtilities.spawnLocalPlayer();
	testRunning->start();
	return true;
}





//Test check commands:


bool FCheckEndedStageSpawned::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();

	ARaceRunningStage* testRunning = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceRunningStage>();
	if (testRunning)
	{
		ARaceEndedStage* testEnded = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceEndedStage>();

		test->TestNotNull(TEXT("Race running next stage should spawn a race ended stage."), testEnded);
		testWorld->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckEndedStageSpawnedWithNoRunningJets::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();

	ARaceRunningStage* testRunning = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceRunningStage>();
	if (testRunning)
	{
		ARaceEndedStage* testEnded = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceEndedStage>();
		bool endedStageSpawned = testEnded ? true : false;
		bool noRunningJets = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameModeMOCK>()->jetsRacing().Num() == 0;

		test->TestNotNull(TEXT("Race running next stage should spawn a race ended stage if no running jets are present."), testEnded);
		testWorld->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckARaceRunningStartEnablesJetsInput::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();

	ARaceRunningStage* testRunning = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceRunningStage>();
	if (testRunning)
	{
		bool jetsHaveInputEnabled = false;

		TArray<AJet*> jets = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameMode>()->jetsRacing().Array();

		for (auto jet : jets)
		{
			jetsHaveInputEnabled = true;
			if (!jet->InputEnabled())
			{
				jetsHaveInputEnabled = false;
				break;
			}
		}

		if (jetsHaveInputEnabled)
		{
			test->TestTrue(TEXT("Race running start should enable jets input."), jetsHaveInputEnabled);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}

		++tickCount;
		if (tickCount > tickLimit)
		{
			test->TestTrue(TEXT("Race running start should enable jets input."), jetsHaveInputEnabled);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}


bool FCheckRaceRunningStartsAnnouncerUIsRemoval::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();

		ARaceRunningStageMOCK* testRunning = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceRunningStageMOCK>();
		if (testRunning)
		{
			if(controllersNeedAnnouncerLoad)
			{
				for (auto iterator = testWorld->GetPlayerControllerIterator(); iterator; ++iterator)
				{
					AProjectRPlayerController* controller = Cast<AProjectRPlayerController, APlayerController>(iterator->Get());
					if(controller == nullptr)
					{
						return false;
					}
					controller->loadAnnouncerUI();
				}
				controllersNeedAnnouncerLoad = false;
				return false;
			}

			testRunning->start();

			TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
			UWidgetBlueprintLibrary::GetAllWidgetsOfClass(sessionUtilities.currentPIEWorld(),retrievedWidgets, UAnnouncerUI::StaticClass(), false);
			
			bool announcerRemovalStarted = testRunning->announcerRemovalDelayStarted();

			if(announcerRemovalStarted)
			{
				test->TestTrue(test->conditionMessage(), announcerRemovalStarted);
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
