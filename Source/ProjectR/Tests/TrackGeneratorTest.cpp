// Fill out your copyright notice in the Description page of Project Settings.






#if WITH_DEV_AUTOMATION_TESTS

#include "TrackGeneratorTest.h"
#include "Commands/TrackGeneratorTestCommands.h"

#include "Track/TrackGenerator.h"
#include "Mocks/TrackGeneratorMOCK.h"

#include "Tests/AutomationEditorCommon.h"




bool FATrackGeneratorIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ATrackGenerator* testGenerator = NewObject<ATrackGenerator>();
	TestNotNull(TEXT("The track generator shouldn't be null when instantiated."), testGenerator);

	return true;
}


bool FATrackGeneratorHasASplineComponentTest::RunTest(const FString& Parameters)
{
	ATrackGeneratorMOCK* testGenerator = NewObject<ATrackGeneratorMOCK>();
	TestTrue(TEXT("The track generator should have a spline component."), testGenerator->hasSplineComponent());

	return true;
}


bool FATrackGeneratorSplineComponentIsTheRootComponentTest::RunTest(const FString& Parameters)
{
	ATrackGeneratorMOCK* testGenerator = NewObject<ATrackGeneratorMOCK>();
	TestTrue(TEXT("The track generator spline component should be the root component."), testGenerator->splineIsRootComponent());

	return true;
}


bool FATrackGeneratorRoadSplinesQuantityIsTheSameAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesQuantityCommand(this));

	return true;
}


bool FATrackGeneratorRoadSplinesStartPositionsAreTheSameAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesStartPositionsCommand(this));

	return true;
}



bool FATrackGeneratorRoadSplinesEndPositionsAreTheSameAsNextSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesEndPositionsCommand(this));

	return true;
}


bool FATrackGeneratorRoadSplinesStartTangentsAreTheSameAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesStartTangentsCommand(this));

	return true;
}


bool FATrackGeneratorRoadSplinesEndTangentsAreTheSameAsNextSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesEndTangentsCommand(this));

	return true;
}


bool FATrackGeneratorRoadSplinesMeshesAreSetAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesMeshesCommand(this));

	return true;
}


bool FATrackGeneratorRoadSplinesMeshesAreTheRoadMeshAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesMeshesAreRoadMeshCommand(this));

	return true;
}


bool FATrackGeneratorHasTheSameAmountOfMagnetSplinesAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplineMagnetSplinesQuantityCommand(this));

	return true;
}


bool FATrackGeneratorMeshesHaveCollisionEnabledAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesCollisionEnabledCommand(this));

	return true;
}


bool FATrackGeneratorMeshesHaveCollisionObjectTypeWorldStaticAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesCollisionObjectTypeCommand(this));

	return true;
}


bool FATrackGeneratorMeshesAreAttachedToRootAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesAttachToRootCommand(this));

	return true;
}


bool FATrackGeneratorMeshesHaveSameMobilityAsRootAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesMobilityCommand(this));

	return true;
}


bool FATrackGeneratorSplineComponentLoopsTest::RunTest(const FString& Parameters)
{
	ATrackGeneratorMOCK* testGenerator = NewObject<ATrackGeneratorMOCK>();
	TestTrue(TEXT("The track generator spline component should loop, these are race tracks."), testGenerator->isSplineComponentLooping());

	return true;
}


bool FATrackGeneratorMagnetSplinesHaveTheSameMobilityAsRoadSplinesAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesMobilityCommand(this));

	return true;
}


bool FATrackGeneratorMagnetSplinesAreAttachedToRoadSplinesAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesAttachToRoadSplinesCommand(this));

	return true;
}


bool FATrackGeneratorMagnetSplinesAreOnTopOfRoadSplinesAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesOnTopRoadSplinesCommand(this));

	return true;
}


bool FATrackGeneratorMagnetSplinesTangentsAreTheSameAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesTangentsCommand(this));

	return true;
}


bool FATrackGeneratorMagnetSplinesMeshesAreSetAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesMeshesCommand(this));

	return true;
}


bool FATrackGeneratorMagnetSplinesAreHiddenInGameTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesVisibilityCommand(this));

	return true;
}


bool FATrackGeneratorMagnetSplinesHaveCollisionEnabledToQueryOnlyTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesCollisionResponseCommand(this));

	return true;
}


bool FATrackGeneratorMagnetSplinesOverlapWithPawnChannelTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesResponseToPawnChannelCommand(this));

	return true;
}


bool FATrackGeneratorMagnetSplinesGenerateOverlapEventsTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesGenerateOverlapEventsCommand(this));

	return true;
}


bool FATrackGeneratorSplineMeshComponentsHaveSmoothInterpolationEnabledTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckComponentsSmoothInterpolationCommand(this));

	return true;
}


bool FATrackGeneratorGeneratesOverlapEventsWhenSpawnedTest::RunTest(const FString& Parameters)
{
	ATrackGenerator* testGenerator = NewObject<ATrackGenerator>();
	TestTrue(TEXT("The track generator should generate overlap events when spawned."), testGenerator->bGenerateOverlapEventsDuringLevelStreaming);

	return true;
}


bool FATrackGeneratorTrackSectionsQuantityMatchesSplinePointsNumberTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckTrackSectionsArrayQuantityAdjustedToNumberOfSplinePointsCommand(this));

	return true;
}


bool FATrackGeneratorSplineMeshComponentsRollAfterSettingRollInEditorTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	float rollValue = 30.0f;
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldRollSplineComponentsCommand(rollValue));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckComponentsRollCommand(rollValue, this));

	return true;
}


bool FATrackGeneratorSplineMeshComponentsWidenAfterSettingWidenInEditorTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	float widthValue = 30.0f;
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldWidenSplineComponentsCommand(widthValue));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckComponentsWidthCommand(widthValue, this));

	return true;
}


bool FATrackGeneratorAllowsDisableCollisionsInEditorTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	float widthValue = 30.0f;
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldDisableCollisionsCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckComponentsCollisionCommand(this));

	return true;
}


bool FATrackGeneratorHaveExpectedCollisionsInPIETest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInPIECommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckComponentsExpectedCollisionInPIECommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FATrackGeneratorSpawnTrackManagerAtBeginPlayTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInPIECommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckTrackGeneratorSpawnsTrackManagerInPIECommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FATrackGeneratorsSpawnOnlyOneTrackManagerAtBeginPlayTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTwoTrackGeneratorsInPIECommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckTrackGeneratorsSpawnOneTrackManagerInPIECommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}










#endif //WITH_DEV_AUTOMATION_TESTS