// Fill out your copyright notice in the Description page of Project Settings.






#if WITH_DEV_AUTOMATION_TESTS

#include "TrackGeneratorTest.h"
#include "TrackGeneratorTestCommands.h"
#include "../../Commands/CommonPIECommands.h"

#include "Track/TrackGenerator.h"
#include "../../Mocks/TrackGeneratorMOCK.h"

#include "Tests/AutomationEditorCommon.h"




bool FATrackGeneratorIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ATrackGenerator* testGenerator = NewObject<ATrackGenerator>();
	TestNotNull(FString("The track generator shouldn't be null when instantiated."), testGenerator);

	return true;
}


bool FATrackGeneratorHasASplineComponentTest::RunTest(const FString& Parameters)
{
	ATrackGeneratorMOCK* testGenerator = NewObject<ATrackGeneratorMOCK>();
	TestTrue(FString("The track generator should have a spline component."), testGenerator->hasSplineComponent());

	return true;
}


bool FATrackGeneratorSplineComponentIsTheRootComponentTest::RunTest(const FString& Parameters)
{
	ATrackGeneratorMOCK* testGenerator = NewObject<ATrackGeneratorMOCK>();
	TestTrue(FString("The track generator spline component should be the root component."), testGenerator->splineIsRootComponent());

	return true;
}


bool FATrackGeneratorRoadSplinesQuantityIsTheSameAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesQuantity(this));

	return true;
}


bool FATrackGeneratorRoadSplinesStartPositionsAreTheSameAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesStartPositions(this));

	return true;
}



bool FATrackGeneratorRoadSplinesEndPositionsAreTheSameAsNextSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesEndPositions(this));

	return true;
}


bool FATrackGeneratorRoadSplinesStartTangentsAreTheSameAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesStartTangents(this));

	return true;
}


bool FATrackGeneratorRoadSplinesEndTangentsAreTheSameAsNextSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesEndTangents(this));

	return true;
}


bool FATrackGeneratorRoadSplinesMeshesAreSetAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesMeshes(this));

	return true;
}


bool FATrackGeneratorRoadSplinesMeshesAreTheRoadMeshAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesMeshesAreRoadMesh(this));

	return true;
}


bool FATrackGeneratorHasTheSameAmountOfMagnetSplinesAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplineMagnetSplinesQuantity(this));

	return true;
}


bool FATrackGeneratorMeshesHaveCollisionEnabledAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesCollisionEnabled(this));

	return true;
}


bool FATrackGeneratorMeshesHaveCollisionObjectTypeWorldStaticAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesCollisionObjectType(this));

	return true;
}


bool FATrackGeneratorMeshesAreAttachedToRootAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesAttachToRoot(this));

	return true;
}


bool FATrackGeneratorMeshesHaveSameMobilityAsRootAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesMobility(this));

	return true;
}


bool FATrackGeneratorSplineComponentLoopsTest::RunTest(const FString& Parameters)
{
	ATrackGeneratorMOCK* testGenerator = NewObject<ATrackGeneratorMOCK>();
	TestTrue(FString("The track generator spline component should loop, these are race tracks."), testGenerator->isSplineComponentLooping());

	return true;
}


bool FATrackGeneratorMagnetSplinesHaveTheSameMobilityAsRoadSplinesAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesMobility(this));

	return true;
}


bool FATrackGeneratorMagnetSplinesAreAttachedToRoadSplinesAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesAttachToRoadSplines(this));

	return true;
}


bool FATrackGeneratorMagnetSplinesAreOnTopOfRoadSplinesAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesOnTopRoadSplines(this));

	return true;
}


bool FATrackGeneratorMagnetSplinesTangentsAreTheSameAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesTangents(this));

	return true;
}


bool FATrackGeneratorMagnetSplinesMeshesAreSetAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesMeshes(this));

	return true;
}


bool FATrackGeneratorMagnetSplinesAreHiddenInGameTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesVisibility(this));

	return true;
}


bool FATrackGeneratorMagnetSplinesHaveCollisionEnabledToQueryOnlyTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesCollisionResponse(this));

	return true;
}


bool FATrackGeneratorMagnetSplinesOverlapWithPawnChannelTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesResponseToPawnChannel(this));

	return true;
}


bool FATrackGeneratorMagnetSplinesGenerateOverlapEventsTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesGenerateOverlapEvents(this));

	return true;
}


bool FATrackGeneratorSplineMeshComponentsHaveSmoothInterpolationEnabledTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckComponentsSmoothInterpolation(this));

	return true;
}


bool FATrackGeneratorGeneratesOverlapEventsWhenSpawnedTest::RunTest(const FString& Parameters)
{
	ATrackGenerator* testGenerator = NewObject<ATrackGenerator>();
	TestTrue(FString("The track generator should generate overlap events when spawned."), testGenerator->bGenerateOverlapEventsDuringLevelStreaming);

	return true;
}


bool FATrackGeneratorTrackSectionsQuantityMatchesSplinePointsNumberTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckTrackSectionsArrayQuantityAdjustedToNumberOfSplinePoints(this));

	return true;
}


bool FATrackGeneratorSplineMeshComponentsRollAfterSettingRollInEditorTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	float rollValue = 30.0f;
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldRollSplineComponents(rollValue));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckComponentsRoll(rollValue, this));

	return true;
}


bool FATrackGeneratorSplineMeshComponentsWidenAfterSettingWidenInEditorTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	float widthValue = 30.0f;
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldWidenSplineComponents(widthValue));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckComponentsWidth(widthValue, this));

	return true;
}


bool FATrackGeneratorAllowsDisableCollisionsInEditorTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	float widthValue = 30.0f;
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldDisableCollisions);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckComponentsCollision(this));

	return true;
}


bool FATrackGeneratorHaveExpectedCollisionsInPIETest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckComponentsExpectedCollisionInPIE(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FATrackGeneratorSpawnTrackManagerAtBeginPlayTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* trackGeneratorClass = ATrackGeneratorMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckTrackGeneratorSpawnsTrackManagerInPIE(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FATrackGeneratorsSpawnOnlyOneTrackManagerAtBeginPlayTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* trackGeneratorClass = ATrackGenerator::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(trackGeneratorClass, FTransform()));
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(trackGeneratorClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckTrackGeneratorsSpawnOneTrackManagerInPIE(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FATrackGeneratorBoundsSplinesQuantityIsTheSameAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/BoundedTrackGeneratorMOCKWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckBoundsSplinesQuantity(this));

	return true;
}


bool FATrackGeneratorBoundsSplinesAreAttachedToRoadSplinesAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/BoundedTrackGeneratorMOCKWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckBoundsSplinesAttachToRoadSplines(this));

	return true;
}


bool FATrackGeneratorBoundsSplinesHaveTheSameMobilityAsRoadSplinesAtSpawningTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/BoundedTrackGeneratorMOCKWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckBoundsSplinesMobility(this));

	return true;
}

















#endif //WITH_DEV_AUTOMATION_TESTS