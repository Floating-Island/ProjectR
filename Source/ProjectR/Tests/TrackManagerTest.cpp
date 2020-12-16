// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "TrackManagerTest.h"
#include "Commands/TrackManagerTestCommands.h"

#include "Track/TrackManager.h"
#include "Tests/AutomationEditorCommon.h"


bool FATrackManagerIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ATrackManager* testManager = NewObject<ATrackManager>();
	TestNotNull(TEXT("The track manager shouldn't be null when instantiated."), testManager);

	return true;
}


bool FATrackManagerHasTrackGeneratorsListedWhenSpawnedTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningATrackGenerator);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckATrackManagerTrackGenerators(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FATrackManagerStoresJetsOverlappingWithTrackGeneratorsTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningARotatedTrackGeneratorAndJetCloseToIt);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckATrackManagerStoresJetsWhenOverlap(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FATrackManagerAttractsJetsTowardsTrackGeneratorsTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningARotatedTrackGeneratorAndJetCloseToIt);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckATrackManagerAttractsJets(tickCount, tickLimit, std::numeric_limits<float>::min(), this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}














#endif //WITH_DEV_AUTOMATION_TESTS