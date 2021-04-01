// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "TrackManagerTest.h"
#include "TrackManagerTestCommands.h"
#include "../../Commands/CommonPIECommands.h"
#include "../../Mocks/TrackManagerMOCK.h"

#include "Track/TrackManager.h"
#include "Track/TrackGenerator.h"

#include "Tests/AutomationEditorCommon.h"


bool FATrackManagerIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ATrackManager* testManager = NewObject<ATrackManager>();
	TestNotNull(TEXT("The track manager shouldn't be null when instantiated."), testManager);

	return true;
}


bool FATrackManagerHasTrackGeneratorsListedWhenSpawnedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The track manager should have track generators already spawned in world."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* trackGeneratorClass = ATrackGenerator::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(trackGeneratorClass, FTransform()));
	
	UClass* trackManagerClass = ATrackManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(trackManagerClass, FTransform()));
	

	ADD_LATENT_AUTOMATION_COMMAND(FCheckATrackManagerTrackGenerators(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FATrackManagerStoresJetsOverlappingWithTrackGeneratorsTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The track manager should store the jets that overlap with a track generator's magnet box."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningARotatedTrackGeneratorAndJetCloseToIt);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckATrackManagerStoresJetsWhenOverlap(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FATrackManagerAttractsJetsTowardsTrackGeneratorsTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The track generator should attract a Jet along the track normal vector when a track manager is present."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningARotatedTrackGeneratorAndJetCloseToIt);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckATrackManagerAttractsJets(std::numeric_limits<float>::min(), this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}














#endif //WITH_DEV_AUTOMATION_TESTS