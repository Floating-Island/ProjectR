// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/RaceGameMode.h"



#include "LapManager/LapManager.h"
#include "Jet/Jet.h"
#include "Track/TrackGenerator.h"
#include "LapPhases/InitialLapPhase.h"
#include "GameMode/RaceStages/RacePreparationStage.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "TimerManager.h"
#include "PlayerController/ProjectRPlayerController.h"
#include "PlayerState/RacePlayerState.h"

#include "Kismet/GameplayStatics.h"


bool ARaceGameMode::expectedControllerQuantityReached()
{
	int controllersAvailable = GetWorld()->GetNumPlayerControllers();
	if(controllersAvailable == expectedControllers())
	{
		return true;
	}
	return false;
}

int ARaceGameMode::expectedControllers()
{
	if(expectedControllersNumber == 0)
	{
		FString controllerQuantityString = UGameplayStatics::ParseOption(OptionsString, "numControllers");//"?numControllers=xx"
		expectedControllersNumber = controllerQuantityString.IsEmpty()? 1 : FCString::Atoi(*controllerQuantityString);
	}
	return expectedControllersNumber;
}

void ARaceGameMode::prepareToStart()
{
	timeToWaitForPlayers = 0.1f;
	FTimerManager& timerManager = GetGameInstance()->GetTimerManager();
	if(timerManager.IsTimerActive(waitForPlayersTimer))
	{
		timerManager.ClearTimer(waitForPlayersTimer);
		timerManager.SetTimerForNextTick(this, &ARaceGameMode::startStage);
	}
}

void ARaceGameMode::startStage()
{
	if(stage)
	{
		stage->start();
	}
}

ARaceGameMode::ARaceGameMode()
{
	expectedControllersNumber = 0;
	numberOfLaps = 3;
	jetSpawnHeight = 100;
	initialForwardDistanceBetweenJets = 3000;
	initialLateralDistanceBetweenJets = 2500;
	stage = nullptr;
	jetClass = AJet::StaticClass();
	currentJetPositions = TMap<AJet*, int8>();
	finalizedJets = TArray<AJet*>();
	timeToWaitForPlayers = 20;
	bPauseable = false;
}

void ARaceGameMode::prepareInitialStageStart()
{
	stage = gameWorld->SpawnActor<ARacePreparationStage>();
	GetGameInstance()->GetTimerManager().SetTimer(waitForPlayersTimer, this, &ARaceGameMode::startStage, timeToWaitForPlayers);
}

void ARaceGameMode::updateCurrentPlayerStateLapOf(AJet* aJet, int aCurrentLap)
{
	AController* controller = Cast<AController, AActor>(aJet->GetOwner());
	if(controller)
	{
		ARacePlayerState* playerState = controller->GetPlayerState<ARacePlayerState>();
		if(playerState && aCurrentLap > playerState->currentLap())
		{
			playerState->updateLapTo(aCurrentLap);
		}
	}
}

void ARaceGameMode::updatePlayerStatesPositions()
{
	for(const auto& jetWithPosition : positions())
	{
		AController* controller = Cast<AController, AActor>(jetWithPosition.Key->GetOwner());
		if(controller)
		{
			ARacePlayerState* playerState = controller->GetPlayerState<ARacePlayerState>();
			if(playerState && jetWithPosition.Value != playerState->currentPosition())
			{
				playerState->updatePositionTo(jetWithPosition.Value);
			}
		}
	}
}

void ARaceGameMode::StartPlay()
{
	Super::StartPlay();
	ClearPause();
	gameWorld = GetWorld();
	AActor* soonToBeTrack = UGameplayStatics::GetActorOfClass(gameWorld, ATrackGenerator::StaticClass());
	track = Cast<ATrackGenerator, AActor>(soonToBeTrack);
	AActor* soonToBeInitialPhase = UGameplayStatics::GetActorOfClass(gameWorld, AInitialLapPhase::StaticClass());
	initialPhase = Cast<AInitialLapPhase, AActor>(soonToBeInitialPhase);
	prepareInitialStageStart();
}

void ARaceGameMode::positionExpectedJets()
{
	int numberOfJetsToCreate = jetsToSpawn();
	float distanceToTrackOrigin = track->distanceAlongSplineOf(initialPhase);
	while (numberOfJetsToCreate > 0)
	{
		distanceToTrackOrigin -= initialForwardDistanceBetweenJets;
		if (distanceToTrackOrigin < 0)
		{
			distanceToTrackOrigin = track->length() + distanceToTrackOrigin;
		}
		FVector segmentRightVector = track->rightVectorAt(distanceToTrackOrigin);
		FVector segmentLocation = track->locationAt(distanceToTrackOrigin);
		FVector segmentUpVector = track->upVectorAt(distanceToTrackOrigin);

		FVector jetLocation = segmentLocation + segmentRightVector * initialLateralDistanceBetweenJets + segmentUpVector * jetSpawnHeight;
		FRotator jetRotation = track->rotationAt(distanceToTrackOrigin);

		createJet(jetLocation, jetRotation, numberOfJetsToCreate);
		if (numberOfJetsToCreate > 0)
		{
			jetLocation = segmentLocation - segmentRightVector * initialLateralDistanceBetweenJets + segmentUpVector * jetSpawnHeight;
			createJet(jetLocation, jetRotation, numberOfJetsToCreate);
		}
	}
}

void ARaceGameMode::createJet(FVector atLocation, FRotator atRotation, int& aNumberOfRemainingJetsToCreate)
{
	AJet* spawnedJet = gameWorld->SpawnActor<AJet>(jetClass, atLocation, atRotation);
	--aNumberOfRemainingJetsToCreate;
	runningJets.Add(spawnedJet);
}

int ARaceGameMode::jetsToSpawn()
{
	return GetWorld()->GetNumPlayerControllers();
}

TSet<AJet*> ARaceGameMode::jetsRacing()
{
	return runningJets;
}

AInitialLapPhase* ARaceGameMode::initialLapPhase()
{
	return initialPhase;
}

void ARaceGameMode::updateStage(ARaceStage* broadcasterStage)
{
	if (broadcasterStage == stage)
	{
		ARaceStage* oldStage = stage;
		stage = stage->nextStage();
		stage->start();
		oldStage->Destroy();
	}
}

TMap<AJet*, int8> ARaceGameMode::calculateJetPositions()
{
	TMap<AJet*, float> scoredPositions = TMap<AJet*, float>();

	for (auto& jet : runningJets)
	{
		float scoredPosition = track->distanceAlongSplineOf(jet) + lapManager->currentLapOf(jet) * track->length();
		scoredPositions.Add(jet, scoredPosition);
	}

	scoredPositions.ValueSort([](float ahead, float behind) {return ahead > behind; });//biggest value = jet ahead of the rest.

	TArray<AJet*> orderedJets = TArray<AJet*>();
	scoredPositions.GenerateKeyArray(orderedJets);

	TMap<AJet*, int8> positions = TMap<AJet*, int8>();
	int8 position = 1;
	for (auto& jet : finalizedJets)
	{
		positions.Add(jet, position);
		++position;
	}
	for (auto& jet : orderedJets)
	{
		positions.Add(jet, position);
		++position;
	}
	return positions;
}

void ARaceGameMode::createLapManager()
{
	lapManager = GetWorld()->SpawnActor<ALapManager>();
	lapManager->subscribeToLapCross(this);
}

void ARaceGameMode::updateJetPositions()
{
	currentJetPositions = calculateJetPositions();
	updatePlayerStatesPositions();
}

int ARaceGameMode::laps()
{
	return numberOfLaps;
}

void ARaceGameMode::lapCompletedByJet(AJet* aCrossingJet)
{
	if (runningJets.Contains(aCrossingJet))
	{	
		if (lapManager->currentLapOf(aCrossingJet) > laps())
		{
			runningJets.Remove(aCrossingJet);
			finalizedJets.Add(aCrossingJet);
			UE_LOG(LogTemp, Log, TEXT("A Jet has finished laps!!!"));
			AProjectRPlayerController* jetController = Cast<AProjectRPlayerController, AActor>(aCrossingJet->GetOwner());
			jetController->loadResultsUI();
		}
		else
		{
			updateCurrentPlayerStateLapOf(aCrossingJet, lapManager->currentLapOf(aCrossingJet));
		}
	}
}

TArray<AJet*> ARaceGameMode::finalistJets()
{
	return finalizedJets;
}

TMap<AJet*, int8> ARaceGameMode::positions()
{
	return currentJetPositions;
}

void ARaceGameMode::playersToCreate(int aPlayerQuantity)
{
	for (int playersCreated = 0; playersCreated < aPlayerQuantity; ++playersCreated)
	{
		UGameplayStatics::CreatePlayer(GetWorld());
	}
}

void ARaceGameMode::achieveNecessaryPlayersQuantity()
{
	int necessaryPlayers = Cast<UProjectRGameInstance, UGameInstance>(GetWorld()->GetGameInstance())->necessaryPlayers();
	int currentPlayers = GetWorld()->GetNumPlayerControllers();
	int playersNeeded = necessaryPlayers - currentPlayers;
	playersToCreate(playersNeeded);
}

void ARaceGameMode::possessJets()
{
	TArray<AJet*> unPossessedJets = runningJets.Array();
	for (auto iterator = GetWorld()->GetPlayerControllerIterator(); iterator; ++iterator)
	{
		APlayerController* controller = iterator->Get();
		AJet* unPossessedJet = unPossessedJets.Pop();
		unPossessedJet->SetOwner(controller);
		controller->Possess(unPossessedJet);
		prepareRaceUIOf(controller);
	}//if when testing the splitscreen only the first player moves, try to spawn more players.
}

void ARaceGameMode::prepareRaceUIOf(APlayerController* aController)
{
	setPlayerStateTotalLaps(aController);
	AProjectRPlayerController* controller = Cast<AProjectRPlayerController, APlayerController>(aController);
	if(controller)
	{
		controller->loadRaceUI();
	}
}

void ARaceGameMode::setPlayerStateTotalLaps(APlayerController* controller)
{
	ARacePlayerState* playerState = Cast<ARacePlayerState, APlayerState>(controller->PlayerState);
	if(playerState)
	{
		playerState->setTotalLapsTo(laps());
	}
}

void ARaceGameMode::disableJetsInput()
{
	for (auto& jet : runningJets)
	{
		if(jet->IsPlayerControlled())
		{
			jet->DisableInput(Cast<APlayerController,AController>(jet->GetController()));
		}
	}
}

void ARaceGameMode::enableJetsInput()
{
	for (auto& jet : runningJets)
	{
		if(jet->IsPlayerControlled())
		{
			jet->EnableInput(Cast<APlayerController,AController>(jet->GetController()));
		}
	}
}

void ARaceGameMode::PostLogin(APlayerController* NewPlayer)
{
	if(expectedControllerQuantityReached())
	{
		prepareToStart();
	}
}

int ARaceGameMode::lapOf(AJet* aJet)
{
	return lapManager->currentLapOf(aJet);
}

int ARaceGameMode::positionOf(AJet* aJet)
{
	return *currentJetPositions.Find(aJet);
}
