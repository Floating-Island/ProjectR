// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "LapManagerTestCommands.h"
#include "LapManager/LapManager.h"
#include "../Mocks/LapManagerMOCK.h"
#include "../Utilities/PIESessionUtilities.h"
#include "LapPhases/InitialLapPhase.h"
#include "LapPhases/IntermediateLapPhase.h"
#include "LapPhases/FinalLapPhase.h"
#include "Jet/Jet.h"



//Test preparation commands:

bool FSpawningALapManagerAndJetCommand::Update()
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


bool FSpawningALapManagerAInitialLapPhaseAndJetCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	sessionUtilities.spawnInPIEAnInstanceOf<AJet>();
	sessionUtilities.spawnInPIEAnInstanceOf<AInitialLapPhase>();
	sessionUtilities.spawnInPIEAnInstanceOf<ALapManagerMOCK>();

	return true;
}


bool FSpawningALapManagerInitalAndIntermediateLapPhasesAndJetCommand::Update()
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
	sessionUtilities.spawnInPIEAnInstanceOf<ALapManagerMOCK>();

	return true;
}


bool FSpawningALapManagerIntermediateAndFinalLapPhasesAndJetCommand::Update()
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


bool FSpawningALapManagerInitialAndFinalLapPhasesAndJetCommand::Update()
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










//Test check commands:


bool FCheckALapManagerStoresJetsCommand::Update()
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
			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("The lap manager should have the jets that are already spawned in world."), hasJetsInWorld);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckJetsInitialLapPhaseCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();
		ALapManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManagerMOCK>();
		if (testManager)
		{
			bool jetsDefaultPhaseIsInitialLapPhase = testManager->defaultLapPhaseIsInitialLapPhase();

			UE_LOG(LogTemp, Log, TEXT("Lap manager jets %s the initial lap phase as default phase."), *FString(jetsDefaultPhaseIsInitialLapPhase ? "have" : "don't have"));

			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("The lap manager jets should have the initial lap phase as default phase."), jetsDefaultPhaseIsInitialLapPhase);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckJetsInitialLapCountCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();
		ALapManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManagerMOCK>();
		if (testManager)
		{
			bool jetsInitialLapCountIsOne = testManager->InitialLapCountSetToOne();

			UE_LOG(LogTemp, Log, TEXT("Lap manager jets %s the initial lap count set as one."), *FString(jetsInitialLapCountIsOne ? "have" : "don't have"));

			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("The lap manager jets should have the initial lap count set to one."), jetsInitialLapCountIsOne);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckJetChangeFromInitialToIntermediateCommand::Update()
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

			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("The jet should change their lap phase from initial to intermediate when overlapping intermediate."), jetsMovedToIntermediatePhase);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckJetChangeFromIntermediateToFinalCommand::Update()
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

			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("The jet should change their lap phase from intermediate to final when overlapping final."), jetsMovedToFinalPhase);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckJetChangeFromFinalToInitialCommand::Update()
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

			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("The jet should change their lap phase from final to initial when overlapping initial."), jetsMovedToInitialPhase);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckJetLapCountChangeFromFinalToInitialCommand::Update()
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
				test->TestTrue(TEXT("The jet should increase its lap count from final to initial phase when overlapping initial."), jetsMovedToInitialPhase && increasedLapCount);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}

			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("Tick Limit reached. The jet should increase its lap count from final to initial phase when overlapping initial."), jetsMovedToInitialPhase && increasedLapCount);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			previousLapCount = currentLapCount;
		}
	}
	return false;
}


#endif //WITH_DEV_AUTOMATION_TESTS
