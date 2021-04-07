// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "LapManagerTest.h"

#include "LapManager/LapManager.h"
//#include "../../Mocks/LapManagerMOCK.h"
#include "LapManagerTestCommands.h"
#include "Tests/AutomationEditorCommon.h"
#include "Jet/SteerStates/CenterSteerState.h"
//#include "../../Commands/CommonPIECommands.h"


bool FALapManagerIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ALapManager* testLapManager = NewObject<ALapManager>();
	TestNotNull(FString("The lap manager shouldn't be null after instantiating it."), testLapManager);

	return true;
}


bool FALapManagerHasJetsListedWhenSpawnedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The lap manager should have the jets that are already spawned in world."));
	establishTickLimitTo(3);
	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerAndJet);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckALapManagerStoresJets(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FALapManagerJetsHaveFinalLapPhaseAsDefaultPhaseTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The lap manager jets should have the final lap phase as default phase."));
	establishTickLimitTo(1);
	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerAFinalLapPhaseAndJet);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetsFinalLapPhase(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FALapManagerJetsHaveInitialLapCountSetToZeroTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The lap manager jets should have the initial lap count set to zero."));
	establishTickLimitTo(1);
	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerAFinalLapPhaseAndJet);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetsInitialLapCount(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FALapManagerJetOverlappingIntermediateChangesPhaseToItFromInitialTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The jet should change their lap phase from initial to intermediate when overlapping intermediate."));
	establishTickLimitTo(1);
	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerInitalAndIntermediateLapPhasesAndJet);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetChangeFromInitialToIntermediate(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FALapManagerJetOverlappingFinalChangesPhaseToItFromIntermediateTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The jet should change their lap phase from intermediate to final when overlapping final."));
	establishTickLimitTo(1);
	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerIntermediateAndFinalLapPhasesAndJet);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetChangeFromIntermediateToFinal(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FALapManagerJetOverlappingInitialChangesPhaseToItFromFinalTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The jet should change their lap phase from final to initial when overlapping initial."));
	establishTickLimitTo(1);
	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerInitialAndFinalLapPhasesAndJet);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetChangeFromFinalToInitial(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FALapManagerJetOverlappingInitialIncreasesLapCountFromFinalTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The jet should increase its lap count from final to initial phase when overlapping initial."));
	establishTickLimitTo(1);
	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerInitialAndFinalLapPhasesAndJet);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetLapCountChangeFromFinalToInitial(std::numeric_limits<int>::max(), this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FALapManagerDoesntTickTest::RunTest(const FString& Parameters)
{
	ALapManager* testManager = NewObject<ALapManager>();

	TestFalse(FString("Should tick every frame."), testManager->CanEverTick());

	return true;
}


bool FALapManagerJetsLastCrossedPhaseIsTheLastOneTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The jet last crossed phase is the last one."));
	establishTickLimitTo(3);
	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerIntermediateAndFinalLapPhasesAndJet);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetLastCrossedPhaseIsFinal(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FALapManagerJetDoesntChangePhaseIfLastCrossedPhaseIsntTheCurrentOneTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The jet doesn't change lap phase if the last one isn't the current one."));
	establishTickLimitTo(3);
	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerIntermediateAndFinalLapPhasesAndJetChangeLastOne);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetLastCrossedPhaseIsStillIntermediate(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FALapManagerEstablishesLapPhasesAllowedMaxDistancesAtBeginPlayTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK"));
	establishTestMessageTo(FString("The lap manager should set the lap phases maximum allowed distance."));
	establishTickLimitTo(3);
	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLapPhasesWithDistancesSet(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS
