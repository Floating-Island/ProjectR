// Fill out your copyright notice in the Description page of Project Settings.






#if WITH_DEV_AUTOMATION_TESTS

#include "RaceStageTestCommands.h"
#include "GameMode/RaceStages/RaceStage.h"
#include "../Mocks/RaceStageMOCK.h"

#include "Tests/AutomationEditorCommon.h"
#include "../Utilities/PIESessionUtilities.h"

//Test preparation commands:

bool FSpawnARaceStageCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	sessionUtilities.spawnInPIEAnInstanceOf<ARaceStageMOCK>();
	
	return true;
}


//Test check commands:


bool FCheckRaceModeSubscribedCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	ARaceStageMOCK* testRaceStage = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceStageMOCK>();
	if (testRaceStage)
	{
		test->TestTrue(TEXT("Race game mode should be subscribed to the stageEndedEvent."), testRaceStage->raceModeIsSubscribed());
		testWorld->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


#endif //WITH_DEV_AUTOMATION_TESTS
