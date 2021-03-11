// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "RaceGameModeTestCommands.h"
#include "GameMode/RaceGameMode.h"
#include "../../Mocks/RaceGameModeMOCK.h"
#include "Jet/Jet.h"
#include "Track/TrackGenerator.h"
#include "LapPhases/InitialLapPhase.h"
#include "LapManager/LapManager.h"
#include "GameMode/RaceStages/RacePreparationStage.h"
#include "GameMode/RaceStages/RaceBeginningStage.h"
#include "GameMode/RaceStages/RaceRunningStage.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "PlayerState/RacePlayerState.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/RaceResultsUI.h"
#include "PlayerController/ProjectRPlayerController.h"

#include "../../Mocks/LapManagerMOCK.h"
#include "Tests/AutomationEditorCommon.h"
#include "../../Utilities/PIESessionUtilities.h"
#include "../../Utilities/NetworkedPIESessionUtilities.h"


//Test preparation commands:


bool FSpawnAJetBehindAnother::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();
	ARaceGameModeMOCK* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameModeMOCK>();

	ATrackGenerator* testTrack = sessionUtilities.retrieveFromPIEAnInstanceOf<ATrackGenerator>();

	float behindDistance = 300;
	int height = 200;
	FVector behind = testTrack->locationAt(behindDistance) + testTrack->upVectorAt(behindDistance) * height;
	float aheadDistance = 1200;
	FVector ahead = testTrack->locationAt(aheadDistance) + testTrack->upVectorAt(aheadDistance) * height;;

	AJet* jetBehind = sessionUtilities.spawnInPIEAnInstanceOf<AJet>(behind);
	AJet* jetAhead = sessionUtilities.spawnInPIEAnInstanceOf<AJet>(ahead);

	testGameMode->createLapManager();

	testGameMode->addToRunningJets(jetBehind);
	testGameMode->addToRunningJets(jetAhead);

	TMap<AJet*, int8> positions = testGameMode->calculateJetPositions();

	bool correctPositions = *positions.Find(jetAhead) < *positions.Find(jetBehind);

	test->TestTrue(TEXT("A jet ahead of another should have its position number lower than the one behind."), correctPositions);
	testWorld->bDebugFrameStepExecution = true;
	return true;
}


bool FSpawnAJetOnFinalLapMakeItFinish::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();
	ARaceGameModeMOCK* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameModeMOCK>();

	ATrackGenerator* testTrack = sessionUtilities.retrieveFromPIEAnInstanceOf<ATrackGenerator>();

	float behindDistance = 700;
	int height = 200;
	FVector behind = testTrack->locationAt(testTrack->length() - behindDistance) + testTrack->upVectorAt(behindDistance) * height;

	AJet* jetBehind = sessionUtilities.spawnInPIEAnInstanceOf<AJet>(behind);

	testGameMode->createLapManagerMOCK();
	testGameMode->addToRunningJets(jetBehind);

	ALapManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManagerMOCK>();
	testManager->makeJetsPhaseFinal();
	testManager->changeLapTo(testGameMode->laps(), jetBehind);

	FVector atInitialPhase = sessionUtilities.retrieveFromPIEAnInstanceOf<AInitialLapPhase>()->GetActorLocation() + testTrack->upVectorAt(behindDistance) * height;
	jetBehind->SetActorLocation(atInitialPhase);

	return true;
}


bool FSpawnAControlledJetOnFinalLapMakeItFinish::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();
	ARaceGameModeMOCK* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameModeMOCK>();

	ATrackGenerator* testTrack = sessionUtilities.retrieveFromPIEAnInstanceOf<ATrackGenerator>();

	float behindDistance = 700;
	int height = 200;
	FVector behind = testTrack->locationAt(testTrack->length() - behindDistance) + testTrack->upVectorAt(behindDistance) * height;

	AJet* jetBehind = sessionUtilities.spawnInPIEAnInstanceOf<AJet>(behind);
	AProjectRPlayerController* testController = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRPlayerController>();

	jetBehind->SetOwner(testController);
	testController->Possess(jetBehind);
	

	testGameMode->createLapManagerMOCK();
	testGameMode->addToRunningJets(jetBehind);

	ALapManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManagerMOCK>();
	testManager->makeJetsPhaseFinal();
	testManager->changeLapTo(testGameMode->laps(), jetBehind);

	FVector atInitialPhase = sessionUtilities.retrieveFromPIEAnInstanceOf<AInitialLapPhase>()->GetActorLocation() + testTrack->upVectorAt(behindDistance) * height;
	jetBehind->SetActorLocation(atInitialPhase);

	return true;
}









//Test check commands:


bool FCheckRaceGameModeSet::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();
	ARaceGameMode* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameMode>();
	if (testGameMode)
	{
		test->TestNotNull(TEXT("Race game mode was succesfully set as game mode in the world."), testGameMode);
		testWorld->bDebugFrameStepExecution = true;
		return true;
	}
	UE_LOG(LogTemp, Log, TEXT("Race game mode not loaded yet."));
	return false;
}


bool FCheckRaceGameModeCreatesAllJets::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();

	ARaceGameMode* testGameMode = Cast<ARaceGameMode, AGameModeBase>(UGameplayStatics::GetGameMode(testWorld));
	if (testGameMode)
	{
		TSet<AJet*> gameModeJets = testGameMode->jetsRacing();
		int expectedNumberOfJets = testGameMode->jetsToSpawn();
		TArray<AJet*> worldJets = sessionUtilities.retrieveFromPIEAllInstancesOf<AJet>();
		bool sameNumberOfJetsInGameMode = gameModeJets.Num() == worldJets.Num() && expectedNumberOfJets == worldJets.Num();

		UE_LOG(LogTemp, Log, TEXT("Expected number of jets: %d."), expectedNumberOfJets);
		UE_LOG(LogTemp, Log, TEXT("Number of race game mode jets: %d."), gameModeJets.Num());
		UE_LOG(LogTemp, Log, TEXT("Number of world jets: %d."), worldJets.Num());
		UE_LOG(LogTemp, Log, TEXT("The race game mode %s the jets in the world."), *FString(sameNumberOfJetsInGameMode ? "has" : "doesn't have"));

		if (sameNumberOfJetsInGameMode)
		{
			test->TestTrue(test->conditionMessage(), sameNumberOfJetsInGameMode);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}

		return test->manageTickCountTowardsLimit();
	}
	return false;
}


bool FCheckRaceGameModeJetsPositioning::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();

	ARaceGameMode* testGameMode = Cast<ARaceGameMode, AGameModeBase>(UGameplayStatics::GetGameMode(testWorld));
	if (testGameMode)
	{
		TSet<AJet*> gameModeJets = testGameMode->jetsRacing();
		int expectedNumberOfJets = testGameMode->jetsToSpawn();
		bool sameNumberOfJetsInGameMode = gameModeJets.Num() == expectedNumberOfJets;
		ATrackGenerator* testTrack = sessionUtilities.retrieveFromPIEAnInstanceOf<ATrackGenerator>();
		AInitialLapPhase* initialPhase = testGameMode->initialLapPhase();
		float distanceBetweenPhaseAndTrack = testTrack->distanceAlongSplineOf(initialPhase);
		if (FMath::IsNearlyZero(distanceBetweenPhaseAndTrack))
		{
			UE_LOG(LogTemp, Log, TEXT("Distance between initial lap phase and track: %f."), distanceBetweenPhaseAndTrack);
			distanceBetweenPhaseAndTrack = testTrack->length();
			UE_LOG(LogTemp, Log, TEXT("Distance between initial lap phase and track: %f. If there's difference, the initial phase is at origin."), distanceBetweenPhaseAndTrack);
		}

		bool jetsAreBehindInitialPhase = true;
		for (const auto& jet : gameModeJets)
		{
			float distanceBetweenJetAndTrack = testTrack->distanceAlongSplineOf(jet);
			UE_LOG(LogTemp, Log, TEXT("Distance between jet and track: %f."), distanceBetweenJetAndTrack);
			if (distanceBetweenJetAndTrack > distanceBetweenPhaseAndTrack)
			{
				jetsAreBehindInitialPhase = false;
				break;
			}
		}

		UE_LOG(LogTemp, Log, TEXT("Expected number of jets: %d."), expectedNumberOfJets);
		UE_LOG(LogTemp, Log, TEXT("Number of race game mode jets: %d."), gameModeJets.Num());


		if (sameNumberOfJetsInGameMode && jetsAreBehindInitialPhase)
		{
			test->TestTrue(test->conditionMessage(), sameNumberOfJetsInGameMode && jetsAreBehindInitialPhase);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}

		return test->manageTickCountTowardsLimit();
	}
	return false;
}


bool FCheckRaceGameModeUpdateStage::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();
	ARaceGameModeMOCK* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameModeMOCK>();

	ARacePreparationStage* testPreparation = sessionUtilities.spawnInPIEAnInstanceOf<ARacePreparationStage>();
	testGameMode->changeStageTo(testPreparation);

	testGameMode->updateStage(testPreparation);

	bool changedStage = ARaceBeginningStage::StaticClass() == testGameMode->currentStage()->GetClass();

	test->TestTrue(TEXT("Race game mode changes the stage to the next when calling updateStage."), changedStage);
	testWorld->bDebugFrameStepExecution = true;
	return true;
}


bool FCheckJetMovedToFinalistJets::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();
	ARaceGameModeMOCK* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameModeMOCK>();
	AJet* testjet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();

	if (testGameMode && testjet)
	{
		bool hasMovedAJetToFinalists = testGameMode->finalistJets().Num() == 1;

		test->TestTrue(TEXT("Race game mode should move a jet to the finalist jets if it completes the final lap."), hasMovedAJetToFinalists);
		testWorld->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckCreatesTheExpectedPlayers::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();
	ARaceGameModeMOCK* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameModeMOCK>();

	if (testGameMode)
	{
		int initialPlayerQuantity = testWorld->GetNumPlayerControllers();
		int playersQuantity = 3;

		testGameMode->playersToCreate(playersQuantity);

		int totalPlayerQuantity = testWorld->GetNumPlayerControllers();

		bool playerQuantityAsExpected = totalPlayerQuantity - initialPlayerQuantity == playersQuantity;

		test->TestTrue(TEXT("Race game mode should create the expected number of players when calling playersToCreate."), playerQuantityAsExpected);
		testWorld->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckCreatesTheNecessaryPlayers::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();
	ARaceGameModeMOCK* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameModeMOCK>();
	UProjectRGameInstance* testGameInstance = Cast<UProjectRGameInstance, UGameInstance>(testWorld->GetGameInstance());

	if (testGameInstance && testGameMode)
	{
		int quantityOfPlayers = 3;
		testGameInstance->expectedPlayers(quantityOfPlayers);
		int necessaryPlayerQuantity = testGameInstance->necessaryPlayers();

		testGameMode->achieveNecessaryPlayersQuantity();

		int totalPlayerQuantity = testWorld->GetNumPlayerControllers();

		bool playerQuantityAsExpected = totalPlayerQuantity == necessaryPlayerQuantity;

		test->TestTrue(TEXT("Race game mode should create the necessary number of players expected from the game instance."), playerQuantityAsExpected);
		testWorld->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckCreatesSameOrMoreJetsThanPlayers::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();
	ARaceGameModeMOCK* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameModeMOCK>();

	if (testGameMode)
	{
		testGameMode->achieveNecessaryPlayersQuantity();
		testGameMode->positionExpectedJets();

		int totalJetsQuantity = sessionUtilities.retrieveFromPIEAllInstancesOf<AJet>().Num();
		UE_LOG(LogTemp, Log, TEXT("number of jets: %d."), totalJetsQuantity);

		int totalPlayerQuantity = testWorld->GetNumPlayerControllers();
		UE_LOG(LogTemp, Log, TEXT("number of players: %d."), totalPlayerQuantity);

		bool playerQuantityAsExpected = totalJetsQuantity >= totalPlayerQuantity;

		if (playerQuantityAsExpected)
		{
			test->TestTrue(test->conditionMessage(), playerQuantityAsExpected);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}

		return test->manageTickCountTowardsLimit();
	}
	return false;
}


bool FCheckJetsSameRotationAsTrack::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.defaultPIEWorld();

	ARaceGameMode* testGameMode = Cast<ARaceGameMode, AGameModeBase>(UGameplayStatics::GetGameMode(testWorld));
	if (testGameMode)
	{
		TSet<AJet*> gameModeJets = testGameMode->jetsRacing();
		if(gameModeJets.Num() > 0)
		{
			ATrackGenerator* testTrack = sessionUtilities.retrieveFromPIEAnInstanceOf<ATrackGenerator>();

			bool jetsWithSameRotationAsTrackSections = false;
			for (const auto& jet : gameModeJets)
			{
				UE_LOG(LogTemp, Log, TEXT("Checking jet."));

				float distanceBetweenJetAndTrack = testTrack->distanceAlongSplineOf(jet);
				UE_LOG(LogTemp, Log, TEXT("Distance between jet and track: %f."), distanceBetweenJetAndTrack);

				FRotator trackSectionRotation = testTrack->rotationAt(distanceBetweenJetAndTrack);
				UE_LOG(LogTemp, Log, TEXT("Track section rotation: %s."), *trackSectionRotation.ToString());

				FRotator jetRotation = jet->GetActorRotation();
				UE_LOG(LogTemp, Log, TEXT("Jet rotation: %s."), *jetRotation.ToString());

				jetsWithSameRotationAsTrackSections = true;
				if (!jetRotation.Equals(trackSectionRotation, 0.01))
				{
					jetsWithSameRotationAsTrackSections = false;
					break;
				}
			}

			if (jetsWithSameRotationAsTrackSections)
			{
				test->TestTrue(test->conditionMessage(), jetsWithSameRotationAsTrackSections);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			return test->manageTickCountTowardsLimit();
		}

	}
	return false;
}


bool FCheckPlayerStateLapUpdated::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
	
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();

		ARaceGameMode* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameMode>();
		ARaceBeginningStage* testStage = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceBeginningStage>();
		if (testGameMode && testStage)
		{
			if(selectedJet == nullptr)
			{
				selectedJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
				return false;
			}

			if(IsValid(selectedJet))
			{
				testGameMode->lapCompletedByJet(selectedJet);
				AController* controller = Cast<AController, AActor>(selectedJet->GetOwner());
				ARacePlayerState* testState = controller->GetPlayerState<ARacePlayerState>();
				if(testState)
				{
					int gameModeCurrentLap = testGameMode->lapOf(selectedJet);
					UE_LOG(LogTemp, Log, TEXT("current game mode lap: %d."), gameModeCurrentLap);
					int playerStateCurrentLap = testState->currentLap();
					UE_LOG(LogTemp, Log, TEXT("current player state lap: %d."), playerStateCurrentLap);
					
					bool lapsMatch = gameModeCurrentLap == playerStateCurrentLap;
					if(lapsMatch)
					{
						test->TestTrue(test->conditionMessage(), lapsMatch);
						sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
						return true;
					}
				}
				return test->manageTickCountTowardsLimit();
			}
		}
	}
	return false;
}


bool FCheckPlayerStatePositionUpdated::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
	
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();

		ARaceGameMode* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameMode>();
		ARaceBeginningStage* testStage = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceBeginningStage>();
		if (testGameMode && testStage)
		{
			if(selectedJet == nullptr)
			{
				selectedJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
				return false;
			}

			if(IsValid(selectedJet))
			{
				testGameMode->updateJetPositions();
				AController* controller = Cast<AController, AActor>(selectedJet->GetOwner());
				ARacePlayerState* testState = controller->GetPlayerState<ARacePlayerState>();
				if(testState)
				{
					int gameModeCurrentPosition = testGameMode->positionOf(selectedJet);
					UE_LOG(LogTemp, Log, TEXT("current game mode position: %d."), gameModeCurrentPosition);
					int playerStateCurrentPosition = testState->currentPosition();
					UE_LOG(LogTemp, Log, TEXT("current player state position: %d."), playerStateCurrentPosition);
					
					bool positionsMatch = gameModeCurrentPosition == playerStateCurrentPosition;
					if(positionsMatch)
					{
						test->TestTrue(test->conditionMessage(), positionsMatch);
						sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
						return true;
					}
				}
				return test->manageTickCountTowardsLimit();
			}
		}
	}
	return false;
}


bool FCheckPlayerStateTotalLapsUpdated::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
	
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();

		ARaceGameMode* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameMode>();
		ARaceBeginningStage* testStage = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceBeginningStage>();
		if (testGameMode && testStage)
		{
			if(selectedJet == nullptr)
			{
				selectedJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
				return false;
			}

			if(IsValid(selectedJet))
			{
				AController* controller = Cast<AController, AActor>(selectedJet->GetOwner());
				ARacePlayerState* testState = controller->GetPlayerState<ARacePlayerState>();
				if(testState)
				{
					int gameModeTotalLaps = testGameMode->laps();
					UE_LOG(LogTemp, Log, TEXT("game mode total laps: %d."), gameModeTotalLaps);
					int playerStateTotalLaps = testState->totalLaps();
					UE_LOG(LogTemp, Log, TEXT("player state total laps: %d."), playerStateTotalLaps);
					
					bool lapsMatch = gameModeTotalLaps == playerStateTotalLaps;
					if(lapsMatch)
					{
						test->TestTrue(test->conditionMessage(), lapsMatch);
						sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
						return true;
					}
				}
				return test->manageTickCountTowardsLimit();
			}
		}
	}
	return false;
}


bool FCheckSameRaceUIQuantityAsControllers::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		ARaceGameMode* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameMode>();
		ARaceBeginningStage* testStage = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceBeginningStage>();
		
		if (testGameMode && testStage)
		{
			UWorld* testWorld = sessionUtilities.defaultPIEWorld();
			TArray<AActor*> controllers = TArray<AActor*>();
			UGameplayStatics::GetAllActorsOfClass(testWorld, AProjectRPlayerController::StaticClass(), controllers);

			TArray<UUserWidget*> raceUIs = TArray<UUserWidget*>();
			UWidgetBlueprintLibrary::GetAllWidgetsOfClass(testWorld,raceUIs, URacePlayerUI::StaticClass(), false);

			int controllersQuantity = controllers.Num();
			UE_LOG(LogTemp, Log, TEXT("controllers: %d."), controllersQuantity);
			int raceUIsQuantity = raceUIs.Num();
			UE_LOG(LogTemp, Log, TEXT("raceUIs: %d."), raceUIsQuantity);
			
			bool quantitiesMatch = controllersQuantity == raceUIsQuantity;

			if(quantitiesMatch)
			{
				test->TestTrue(test->conditionMessage(), quantitiesMatch);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
			return test->manageTickCountTowardsLimit();
		}
	}
	return false;
}


bool FCheckServerRaceGameModePreventsPausing::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		FWorldContext serverContext = NetworkedPIESessionUtilities::retrieveServerWorldContext(clientQuantity);
		UWorld* serverWorld = serverContext.World();
		if(serverWorld)
		{
			FWorldContext clientContext = NetworkedPIESessionUtilities::retrieveClientWorldContext();
			UWorld* clientWorld = clientContext.World();
			if(clientWorld)
			{
				bool preventsPausing = serverWorld->GetAuthGameMode()->AllowPausing() == false;

				if(preventsPausing)
				{
					test->TestTrue(test->conditionMessage(), preventsPausing);
					for(auto context : GEditor->GetWorldContexts())
					{
						context.World()->bDebugFrameStepExecution = true;
					}
					return true;
				}
				return test->manageTickCountTowardsLimit();
			}
		}
	}
	return false;
}


bool FCheckGameModeRaceResultsLoaded::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		ARaceGameMode* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameMode>();
		
		if (testGameMode)
		{
			UWorld* testWorld = sessionUtilities.defaultPIEWorld();
			TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
			UWidgetBlueprintLibrary::GetAllWidgetsOfClass(testWorld,retrievedWidgets, URaceResultsUI::StaticClass(), false);

			bool hasLoadedResults = retrievedWidgets.Num() > 0;

			if(hasLoadedResults)
			{
				test->TestTrue(test->conditionMessage(), hasLoadedResults);
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
