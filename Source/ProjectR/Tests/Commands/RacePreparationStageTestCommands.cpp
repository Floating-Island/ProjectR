// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "RacePreparationStageTestCommands.h"
#include "LapManager/LapManager.h"
#include "GameMode/RaceStages/RacePreparationStage.h"
#include "GameMode/RaceStages/RaceBeginningStage.h"
#include "GameInstance/ProjectRGameInstance.h"

#include "Tests/AutomationEditorCommon.h"
#include "../Utilities/PIESessionUtilities.h"

//Test preparation commands:


bool FSpawnARacePreparationStageCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();

	ARacePreparationStage* testPreparation = sessionUtilities.retrieveFromPIEAnInstanceOf<ARacePreparationStage>();
	if (testPreparation == nullptr)
	{
		testPreparation = sessionUtilities.spawnInPIEAnInstanceOf<ARacePreparationStage>();
	}
	ARaceBeginningStage* testBeginning = Cast<ARaceBeginningStage, ARaceStage>(testPreparation->nextStage());

	test->TestNotNull(TEXT("The race preparation stage's nextStage should spawn a race beginning stage in the world."), testBeginning);
	testWorld->bDebugFrameStepExecution = true;
	return true;
}


bool FSpawnARacePreparationMakeItStartCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	ARacePreparationStage* testPreparation = sessionUtilities.spawnInPIEAnInstanceOf<ARacePreparationStage>();

	testPreparation->start();
	return true;
}








//Test check commands:


bool FCheckLapManagerSpawnedCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();

	ARacePreparationStage* testPreparation = sessionUtilities.retrieveFromPIEAnInstanceOf<ARacePreparationStage>();
	if (testPreparation)
	{
		ALapManager* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManager>();

		test->TestNotNull(TEXT("Race preparation start should spawn a lap manager."), testManager);
		testWorld->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckPlayersQuantityOnStartCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();

		ARacePreparationStage* testPreparation = sessionUtilities.retrieveFromPIEAnInstanceOf<ARacePreparationStage>();
		if (testPreparation)
		{
			if (stageHasStarted)
			{
				int numberOfPlayers = testWorld->GetNumPlayerControllers();
				int necessaryPlayers = Cast<UProjectRGameInstance, UGameInstance>(testWorld->GetGameInstance())->necessaryPlayers();

				aTest->TestTrue(TEXT("Race preparation start should generate the remaining necessary players in the game."), numberOfPlayers == necessaryPlayers);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			else
			{
				testPreparation->start();
				stageHasStarted = true;
			}
		}
		else
		{
			sessionUtilities.spawnInPIEAnInstanceOf<ARacePreparationStage>();
		}
	}
	return false;
}




#endif //WITH_DEV_AUTOMATION_TESTS
