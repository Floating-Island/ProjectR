// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "RaceRunningStageTestCommands.h"
#include "GameMode/RaceStages/RaceRunningStage.h"
#include "GameMode/RaceStages/RaceEndedStage.h"

#include "../Mocks/RaceGameModeMOCK.h"
#include "../Utilities/PIESessionUtilities.h"

//Test preparation commands:

bool FSpawnARaceRunningCallNextStageCommand::Update()
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


bool FSpawnARaceRunningCommand::Update()
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





//Test check commands:


bool FCheckEndedStageSpawnedCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.currentPIEWorld();

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


bool FCheckEndedStageSpawnedWithNoRunningJetsCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.currentPIEWorld();

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


#endif //WITH_DEV_AUTOMATION_TESTS
