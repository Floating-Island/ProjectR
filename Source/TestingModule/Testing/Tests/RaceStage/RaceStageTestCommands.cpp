// Fill out your copyright notice in the Description page of Project Settings.






#if WITH_DEV_AUTOMATION_TESTS

#include "RaceStageTestCommands.h"
#include "../../Mocks/RaceStageMOCK.h"

#include "Tests/AutomationEditorCommon.h"
#include "../../Utilities/PIESessionUtilities.h"

//Test preparation commands:


//Test check commands:


bool FCheckRaceModeSubscribed::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();

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
