// Fill out your copyright notice in the Description page of Project Settings.






#if WITH_DEV_AUTOMATION_TESTS

#include "RaceGameModeTestCommands.h"
#include "GameMode/RaceGameMode.h"
#include "../Mocks/RaceGameModeMOCK.h"
#include "Jet/Jet.h"
#include "Track/TrackGenerator.h"
#include "LapPhases/InitialLapPhase.h"
#include "LapManager/LapManager.h"
#include "GameMode/RaceStages/RacePreparationStage.h"
#include "GameMode/RaceStages/RaceBeginningStage.h"
#include "GameMode/RaceStages/RaceRunningStage.h"
#include "GameInstance/ProjectRGameInstance.h"

#include "../Mocks/LapManagerMOCK.h"
#include "Tests/AutomationEditorCommon.h"
#include "../Utilities/PIESessionUtilities.h"


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
			test->TestTrue(TEXT("Race game mode should have the same number of jets than the world."), sameNumberOfJetsInGameMode);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}

		++aTickCount;
		if (aTickCount > aTickLimit)
		{
			test->TestTrue(TEXT("Tick limit reached. Race game mode should have the same number of jets than the world."), sameNumberOfJetsInGameMode);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}
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
			test->TestTrue(TEXT("Race game mode should position the jets behind the initial lap phase."), sameNumberOfJetsInGameMode && jetsAreBehindInitialPhase);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}

		++aTickCount;
		if (aTickCount > aTickLimit)
		{
			test->TestTrue(TEXT("Tick limit reached. Race game mode should position the jets behind the initial lap phase."), sameNumberOfJetsInGameMode && jetsAreBehindInitialPhase);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}
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
			aTest->TestTrue(TEXT("Race game mode should create the same or more jets than players."), playerQuantityAsExpected);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}

		++aTickCount;
		if (aTickCount > aTickLimit)
		{
			aTest->TestTrue(TEXT("Race game mode should create the same or more jets than players."), playerQuantityAsExpected);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}
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
		ATrackGenerator* testTrack = sessionUtilities.retrieveFromPIEAnInstanceOf<ATrackGenerator>();

		bool jetsWithSameRotationAsTrackSections = false;
		for (const auto& jet : gameModeJets)
		{
			float distanceBetweenJetAndTrack = testTrack->distanceAlongSplineOf(jet);
			FRotator trackSectionRotation = testTrack->rotationAt(distanceBetweenJetAndTrack);
			FRotator jetRotation = jet->GetActorRotation();

			jetsWithSameRotationAsTrackSections = true;
			if (!jetRotation.Equals(trackSectionRotation, 0.01))
			{
				jetsWithSameRotationAsTrackSections = false;
				break;
			}
		}

		if (jetsWithSameRotationAsTrackSections)
		{
			aTest->TestTrue(TEXT("Race game mode should coincede jets rotation with their track section rotation."), jetsWithSameRotationAsTrackSections);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}

		++aTickCount;
		if (aTickCount > aTickLimit)
		{
			aTest->TestTrue(TEXT("Tick limit reached. Race game mode should coincede jets rotation with their track section rotation."), jetsWithSameRotationAsTrackSections);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}






#endif //WITH_DEV_AUTOMATION_TESTS
