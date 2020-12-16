// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "RacePreparationStageTestCommands.h"
#include "LapManager/LapManager.h"
#include "GameMode/RaceStages/RacePreparationStage.h"
#include "GameMode/RaceStages/RaceBeginningStage.h"
#include "GameMode/RaceGameMode.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "Jet/Jet.h"
#include "GameFramework/PlayerController.h"

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

				if (requiredPlayerQuantityAchieved)
				{
					aTest->TestTrue(TEXT("Race preparation start should generate the remaining necessary players in the game."), requiredPlayerQuantityAchieved);
					testWorld->bDebugFrameStepExecution = true;
					return true;
				}

				++aTickCount;
				if (aTickCount > aTickLimit)
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

				for (auto iterator = testWorld->GetPlayerControllerIterator(); iterator; ++iterator)
				{
					APlayerController* controller = iterator->Get();
					AJet* controlledJet = Cast<AJet, APawn>(controller->GetPawn());
					UE_LOG(LogTemp, Log, TEXT("this pawn %s a jet."), *FString(controlledJet ? "is" : "isn't"));
					if (!controlledJet)
					{
						controllersPossessJets = false;
						break;
					}
				}

				int numberOfPlayers = testWorld->GetNumPlayerControllers();
				UE_LOG(LogTemp, Log, TEXT("number of player controllers in world: %d."), numberOfPlayers);
				int necessaryPlayers = Cast<UProjectRGameInstance, UGameInstance>(testWorld->GetGameInstance())->necessaryPlayers();
				UE_LOG(LogTemp, Log, TEXT("number of necessary player controllers in world: %d."), necessaryPlayers);



				if (controllersPossessJets)
				{
					aTest->TestTrue(TEXT("Race preparation start should make the controllers possess the jets."), controllersPossessJets);
					testWorld->bDebugFrameStepExecution = true;
					return true;
				}

				++aTickCount;
				if (aTickCount > aTickLimit)
				{
					aTest->TestTrue(TEXT("Tick limit reached, race preparation start should generate the remaining necessary players in the game."), controllersPossessJets);
					testWorld->bDebugFrameStepExecution = true;
					return true;
				}
			}
			else
			{
				sessionUtilities.spawnLocalPlayer();//if expectedPlayers in game instance is set to 1. If more, spawn more.
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


bool FCheckJetsInputDisabled::Update()
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
				bool jetsHaveInputDisabled = false;

				TArray<AJet*> jets = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameMode>()->jetsRacing().Array();

				for (auto jet : jets)
				{
					jetsHaveInputDisabled = true;
					if (jet->InputEnabled())
					{
						jetsHaveInputDisabled = false;
						break;
					}
				}
				
				if (jetsHaveInputDisabled)
				{
					aTest->TestTrue(TEXT("Race preparation start should disable the jets input."), jetsHaveInputDisabled);
					testWorld->bDebugFrameStepExecution = true;
					return true;
				}

				++aTickCount;
				if (aTickCount > aTickLimit)
				{
					aTest->TestTrue(TEXT("Tick limit reached, race preparation start should disable the jets input."), jetsHaveInputDisabled);
					testWorld->bDebugFrameStepExecution = true;
					return true;
				}
			}
			else
			{
				sessionUtilities.spawnLocalPlayer();//if expectedPlayers in game instance is set to 1. If more, spawn more.
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
