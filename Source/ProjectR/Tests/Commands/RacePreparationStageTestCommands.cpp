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
				UE_LOG(LogTemp, Log, TEXT("number of player controllers in world: %d."), numberOfPlayers);
				int necessaryPlayers = Cast<UProjectRGameInstance, UGameInstance>(testWorld->GetGameInstance())->necessaryPlayers();
				UE_LOG(LogTemp, Log, TEXT("number of necessary player controllers in world: %d."), necessaryPlayers);

				bool requiredPlayerQuantityAchieved = numberOfPlayers == necessaryPlayers;

				if(requiredPlayerQuantityAchieved)
				{
					aTest->TestTrue(TEXT("Race preparation start should generate the remaining necessary players in the game."), requiredPlayerQuantityAchieved);
					testWorld->bDebugFrameStepExecution = true;
					return true;
				}

				++aTickCount;
				if(aTickCount > aTickLimit)
				{
					aTest->TestTrue(TEXT("Tick limit reached, race preparation start should generate the remaining necessary players in the game."), requiredPlayerQuantityAchieved);
					testWorld->bDebugFrameStepExecution = true;
					return true;
				}
			}
			else
			{
				int expectedPlayersInGame = 3;
				UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(testWorld->GetGameInstance());
				gameInstance->expectedPlayers(expectedPlayersInGame);
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


bool FCheckPlayersPossessingJets::Update()
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
				bool controllersPossessJets = true;

				for(auto iterator = testWorld->GetPlayerControllerIterator(); iterator; ++iterator )
				{
					APlayerController* controller = iterator->Get();
					AJet* controlledJet = Cast<AJet, AActor>(controller->AcknowledgedPawn);
					if(!controlledJet)
					{
						controllersPossessJets = false;
						break;
					}
				}
				
				int numberOfPlayers = testWorld->GetNumPlayerControllers();
				UE_LOG(LogTemp, Log, TEXT("number of player controllers in world: %d."), numberOfPlayers);
				int necessaryPlayers = Cast<UProjectRGameInstance, UGameInstance>(testWorld->GetGameInstance())->necessaryPlayers();
				UE_LOG(LogTemp, Log, TEXT("number of necessary player controllers in world: %d."), necessaryPlayers);

				

				if(controllersPossessJets)
				{
					aTest->TestTrue(TEXT("Race preparation start should make the controllers possess the jets."), controllersPossessJets);
					testWorld->bDebugFrameStepExecution = true;
					return true;
				}

				++aTickCount;
				if(aTickCount > aTickLimit)
				{
					aTest->TestTrue(TEXT("Tick limit reached, race preparation start should generate the remaining necessary players in the game."), controllersPossessJets);
					testWorld->bDebugFrameStepExecution = true;
					return true;
				}
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
