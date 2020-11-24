// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "RaceBeginningStageTestCommands.h"
#include "GameMode/RaceStages/RaceBeginningStage.h"
#include "../Mocks/RaceBeginningStageMOCK.h"
#include "GameMode/RaceStages/RaceRunningStage.h"


#include "Tests/AutomationEditorCommon.h"
#include "../Utilities/PIESessionUtilities.h"

//Test preparation commands:

bool FSpawnARaceBeginningMOCKCommand::Update()
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


bool FSpawnARaceBeginningCallCountdownStartCommand::Update()
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

bool FCheckTimerActiveCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	ARaceBeginningStageMOCK* testBeginning = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceBeginningStageMOCK>();
	if (testBeginning)
	{
		test->TestTrue(TEXT("Race beginning stage should have its timer active at start."), testBeginning->hasTimerActive());
		testWorld->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckRunningStageSpawnedCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.currentPIEWorld();

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



#endif //WITH_DEV_AUTOMATION_TESTS
