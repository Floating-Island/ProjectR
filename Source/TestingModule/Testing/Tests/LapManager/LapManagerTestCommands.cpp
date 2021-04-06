// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "LapManagerTestCommands.h"
#include "LapManager/LapManager.h"
#include "../../Mocks/LapManagerMOCK.h"
#include "../../Utilities/PIESessionUtilities.h"
#include "LapPhases/InitialLapPhase.h"
#include "LapPhases/IntermediateLapPhase.h"
#include "LapPhases/FinalLapPhase.h"
#include "Jet/Jet.h"



//Test preparation commands:

bool FSpawningALapManagerAndJet::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	sessionUtilities.spawnInPIEAnInstanceOf<AJet>();
	sessionUtilities.spawnInPIEAnInstanceOf<ALapManager>();

	return true;
}


bool FSpawningALapManagerAFinalLapPhaseAndJet::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	sessionUtilities.spawnInPIEAnInstanceOf<AJet>();
	sessionUtilities.spawnInPIEAnInstanceOf<AFinalLapPhase>();
	sessionUtilities.spawnInPIEAnInstanceOf<ALapManagerMOCK>();

	return true;
}


bool FSpawningALapManagerInitalAndIntermediateLapPhasesAndJet::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	FVector jetLocation = FVector(0, 0, -100);
	sessionUtilities.spawnInPIEAnInstanceOf<AJet>(jetLocation);
	sessionUtilities.spawnInPIEAnInstanceOf<AInitialLapPhase>();
	FVector intermediatePhaseLocation = jetLocation + FVector(0, 0, -20);
	sessionUtilities.spawnInPIEAnInstanceOf<AIntermediateLapPhase>(intermediatePhaseLocation);
	ALapManagerMOCK* testManager = sessionUtilities.spawnInPIEAnInstanceOf<ALapManagerMOCK>();
	testManager->makeJetsPhaseInitial();

	return true;
}


bool FSpawningALapManagerIntermediateAndFinalLapPhasesAndJet::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	FVector jetLocation = FVector(0, 0, -100);
	sessionUtilities.spawnInPIEAnInstanceOf<AJet>(jetLocation);
	sessionUtilities.spawnInPIEAnInstanceOf<AIntermediateLapPhase>();
	FVector finalPhaseLocation = jetLocation + FVector(0, 0, -20);
	sessionUtilities.spawnInPIEAnInstanceOf<AFinalLapPhase>(finalPhaseLocation);
	ALapManagerMOCK* testManager = sessionUtilities.spawnInPIEAnInstanceOf<ALapManagerMOCK>();
	testManager->makeJetsPhaseIntermediate();

	return true;
}


bool FSpawningALapManagerInitialAndFinalLapPhasesAndJet::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	FVector jetLocation = FVector(0, 0, -100);
	sessionUtilities.spawnInPIEAnInstanceOf<AJet>(jetLocation);
	sessionUtilities.spawnInPIEAnInstanceOf<AFinalLapPhase>();
	FVector initialPhaseLocation = jetLocation + FVector(0, 0, -20);
	sessionUtilities.spawnInPIEAnInstanceOf<AInitialLapPhase>(initialPhaseLocation);
	ALapManagerMOCK* testManager = sessionUtilities.spawnInPIEAnInstanceOf<ALapManagerMOCK>();
	testManager->makeJetsPhaseFinal();

	return true;
}


bool FSpawningALapManagerIntermediateAndFinalLapPhasesAndJetChangeLastOne::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	FVector jetLocation = FVector(0, 0, -100);
	sessionUtilities.spawnInPIEAnInstanceOf<AJet>(jetLocation);
	sessionUtilities.spawnInPIEAnInstanceOf<AIntermediateLapPhase>();
	FVector finalPhaseLocation = jetLocation + FVector(0, 0, -20);
	sessionUtilities.spawnInPIEAnInstanceOf<AFinalLapPhase>(finalPhaseLocation);
	ALapManagerMOCK* testManager = sessionUtilities.spawnInPIEAnInstanceOf<ALapManagerMOCK>();
	testManager->makeJetsPhaseIntermediate();
	testManager->makeLastCrossedPhaseFinal();

	return true;
}









//Test check commands:


bool FCheckALapManagerStoresJets::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();
		ALapManager* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManager>();
		if (testManager)
		{
			bool hasJetsInWorld = testManager->jetsInPlay().Contains(sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>());

			UE_LOG(LogTemp, Log, TEXT("Lap manager %s the jets listed."), *FString(hasJetsInWorld ? "has" : "doesn't have"));
			test->increaseTickCount();
			if (test->tickCountExceedsLimit())
			{
				test->TestTrue(test->conditionMessage(), hasJetsInWorld);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckJetsFinalLapPhase::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();
		ALapManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManagerMOCK>();
		if (testManager)
		{
			bool jetsDefaultPhaseIsFinalLapPhase = testManager->defaultLapPhaseIsFinalLapPhase();

			UE_LOG(LogTemp, Log, TEXT("Lap manager jets %s the final lap phase as default phase."), *FString(jetsDefaultPhaseIsFinalLapPhase ? "have" : "don't have"));

			test->increaseTickCount();
			if (test->tickCountExceedsLimit())
			{
				test->TestTrue(test->conditionMessage(), jetsDefaultPhaseIsFinalLapPhase);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckJetsInitialLapCount::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();
		ALapManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManagerMOCK>();
		if (testManager)
		{
			bool jetsInitialLapCountIsZero = testManager->InitialLapCountSetToZero();

			UE_LOG(LogTemp, Log, TEXT("Lap manager jets %s the initial lap count set as zero."), *FString(jetsInitialLapCountIsZero ? "have" : "don't have"));

			test->increaseTickCount();
			if (test->tickCountExceedsLimit())
			{
				test->TestTrue(test->conditionMessage(), jetsInitialLapCountIsZero);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckJetChangeFromInitialToIntermediate::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		ALapManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManagerMOCK>();
		if (testManager)
		{
			bool jetsMovedToIntermediatePhase = testManager->jetsMovedFromInitialToIntermediatePhase();

			UE_LOG(LogTemp, Log, TEXT("Jet location: %s."), *testJet->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jets %s lap phase from initial to intermediate when overlapping intermediate."), *FString(jetsMovedToIntermediatePhase ? "changes" : "doesn't change"));

			test->increaseTickCount();
			if (test->tickCountExceedsLimit())
			{
				test->TestTrue(test->conditionMessage(), jetsMovedToIntermediatePhase);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckJetChangeFromIntermediateToFinal::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		ALapManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManagerMOCK>();
		if (testManager)
		{
			bool jetsMovedToFinalPhase = testManager->jetsMovedFromIntermediateToFinalPhase();

			UE_LOG(LogTemp, Log, TEXT("Jet location: %s."), *testJet->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jets %s lap phase from intermediate to final when overlapping final."), *FString(jetsMovedToFinalPhase ? "changes" : "doesn't change"));

			test->increaseTickCount();
			if (test->tickCountExceedsLimit())
			{
				test->TestTrue(test->conditionMessage(), jetsMovedToFinalPhase);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckJetChangeFromFinalToInitial::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		ALapManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManagerMOCK>();
		if (testManager)
		{
			bool jetsMovedToInitialPhase = testManager->jetsMovedFromFinalToInitialPhase();

			UE_LOG(LogTemp, Log, TEXT("Jet location: %s."), *testJet->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jets %s lap phase from final to initial when overlapping initial."), *FString(jetsMovedToInitialPhase ? "changes" : "doesn't change"));

			test->increaseTickCount();
			if (test->tickCountExceedsLimit())
			{
				test->TestTrue(test->conditionMessage(), jetsMovedToInitialPhase);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckJetLapCountChangeFromFinalToInitial::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		ALapManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManagerMOCK>();
		if (testManager)
		{
			int currentLapCount = testManager->currentLapOf(testJet);
			bool jetsMovedToInitialPhase = testManager->jetsMovedFromFinalToInitialPhase();
			bool increasedLapCount = currentLapCount == previousLapCount + 1;

			UE_LOG(LogTemp, Log, TEXT("Jet location: %s."), *testJet->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jets %s lap phase from final to initial when overlapping initial."), *FString(jetsMovedToInitialPhase ? "changes" : "doesn't change"));
			UE_LOG(LogTemp, Log, TEXT("Jet previous lap count: %d."), previousLapCount);
			UE_LOG(LogTemp, Log, TEXT("Jet current lap count: %d."), currentLapCount);
			UE_LOG(LogTemp, Log, TEXT("Jets %s increased its lap count."), *FString(increasedLapCount ? "has" : "hasn't"));

			if (increasedLapCount)
			{
				test->TestTrue(test->conditionMessage(), jetsMovedToInitialPhase && increasedLapCount);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			previousLapCount = currentLapCount;
			return test->manageTickCountTowardsLimit();
		}
	}
	return false;
}


bool FCheckJetLastCrossedPhaseIsFinal::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		ALapManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManagerMOCK>();
		if (testManager)
		{
			bool jetLastCrossedPhaseIsFinalLapPhase = testManager->lastCrossedPhaseIs(AFinalLapPhase::StaticClass(), testJet);

			UE_LOG(LogTemp, Log, TEXT("Lap manager jet %s the final lap phase as the last crossed one."), *FString(jetLastCrossedPhaseIsFinalLapPhase ? "have" : "don't have"));

			test->increaseTickCount();
			if (test->tickCountExceedsLimit())
			{
				test->TestTrue(test->conditionMessage(), jetLastCrossedPhaseIsFinalLapPhase);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckJetLastCrossedPhaseIsStillIntermediate::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		ALapManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManagerMOCK>();
		if (testManager)
		{
			bool jetLastCrossedPhaseIsFinalLapPhase = testManager->lastCrossedPhaseIs(AFinalLapPhase::StaticClass(), testJet);
			bool jetCurrentPhaseIsIntermediate = testManager->currentRecordedPhaseClassOf(testJet) == AIntermediateLapPhase::StaticClass();

			UE_LOG(LogTemp, Log, TEXT("Lap manager jet %s the final lap phase as the last crossed one."), *FString(jetLastCrossedPhaseIsFinalLapPhase ? "have" : "don't have"));
			UE_LOG(LogTemp, Log, TEXT("Lap manager jet %s the intermediate lap phase."), *FString(jetLastCrossedPhaseIsFinalLapPhase ? "is" : "isn't"));

			test->increaseTickCount();
			if (test->tickCountExceedsLimit())
			{
				test->TestTrue(test->conditionMessage(), jetLastCrossedPhaseIsFinalLapPhase && jetCurrentPhaseIsIntermediate);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
