// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackGeneratorTest.h"

#include "Track/TrackGenerator.h"
#include "Mocks/TrackGeneratorMOCK.h"

#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Editor.h"
#include "../../../../../Program Files/Epic Games/UE_4.25/Engine/Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Engine.h"



#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName.
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorIsntNullWhenInstantiatedTest, "ProjectR.TrackGenerator Tests.Unit.000: Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ATrackGenerator* testGenerator = NewObject<ATrackGenerator>();
	{
		TestNotNull(TEXT("The track generator shouldn't be null when instantiated."), testGenerator);
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorHasASplineComponentTest, "ProjectR.TrackGenerator Tests.Unit.001: Has a spline component", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorHasASplineComponentTest::RunTest(const FString& Parameters)
{
	ATrackGeneratorMOCK* testGenerator = NewObject<ATrackGeneratorMOCK>();
	{
		TestTrue(TEXT("The track generator should have a spline component."), testGenerator->hasSplineComponent());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineComponentIsTheRootComponentTest, "ProjectR.TrackGenerator Tests.Unit.002: Spline component is the root component", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorSplineComponentIsTheRootComponentTest::RunTest(const FString& Parameters)
{
	ATrackGeneratorMOCK* testGenerator = NewObject<ATrackGeneratorMOCK>();
	{
		TestTrue(TEXT("The track generator spline component should be the root component."), testGenerator->splineIsRootComponent());
	}

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

bool FSpawnTrackGeneratorInEditorWorldCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}

	UWorld* testWorld = GEditor->GetEditorWorldContext().World();

	testWorld->SpawnActor<ATrackGeneratorMOCK>(ATrackGeneratorMOCK::StaticClass());

	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRoadSplinesQuantityCommand, FAutomationTestBase*, test);

bool FCheckRoadSplinesQuantityCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{
		int32 roadSplinesQuantity = testGenerator->roadSplinesQuantity();
		int32 splinePointsQuantity = testGenerator->splinePointsQuantity();
		bool sameAmountOfSplinePointsAsRoadSplines = roadSplinesQuantity == splinePointsQuantity;//splines always have start and end points at the beginning...
		UE_LOG(LogTemp, Log, TEXT("Spline points quantity in generator: %d."), splinePointsQuantity);
		UE_LOG(LogTemp, Log, TEXT("Road splines quantity in generator: %d."), roadSplinesQuantity);
		UE_LOG(LogTemp, Log, TEXT("Road splines quantity is coincident with number of spline points: %s."), *FString(sameAmountOfSplinePointsAsRoadSplines ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the number of road splines should be coincident with the spline points quantity."), sameAmountOfSplinePointsAsRoadSplines);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorRoadSplinesQuantityIsTheSameAsSplinePointsAtSpawningTest, "ProjectR.TrackGenerator Tests.Unit.003: Road splines quantity is the same as spline points at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorRoadSplinesQuantityIsTheSameAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesQuantityCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRoadSplinesStartPositionsCommand, FAutomationTestBase*, test);

bool FCheckRoadSplinesStartPositionsCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesStartPositionsMatchSplinePoints = testGenerator->roadSplinesAndPointsHaveSameStartPositions();
		UE_LOG(LogTemp, Log, TEXT("Road splines start positions are coincident with the positions of spline points: %s."), *FString(roadSplinesStartPositionsMatchSplinePoints ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the start positions of road splines should be coincident with the spline points positions."), roadSplinesStartPositionsMatchSplinePoints);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorRoadSplinesStartPositionsAreTheSameAsSplinePointsAtSpawningTest, "ProjectR.TrackGenerator Tests.Unit.004: Road splines start positions are the same as spline points at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorRoadSplinesStartPositionsAreTheSameAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesStartPositionsCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRoadSplinesEndPositionsCommand, FAutomationTestBase*, test);

bool FCheckRoadSplinesEndPositionsCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesEndPositionsMatchSplinePoints = testGenerator->roadSplinesAndPointsHaveSameEndPositions();
		UE_LOG(LogTemp, Log, TEXT("Road splines end positions are coincident with the positions of next spline points: %s."), *FString(roadSplinesEndPositionsMatchSplinePoints ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the end positions of road splines should be coincident with the next spline points positions."), roadSplinesEndPositionsMatchSplinePoints);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorRoadSplinesEndPositionsAreTheSameAsNextSplinePointsAtSpawningTest, "ProjectR.TrackGenerator Tests.Unit.005: Road splines end positions are the same as next spline points at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorRoadSplinesEndPositionsAreTheSameAsNextSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesEndPositionsCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRoadSplinesStartTangentsCommand, FAutomationTestBase*, test);

bool FCheckRoadSplinesStartTangentsCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesStartTangentsMatchSplinePoints = testGenerator->roadSplinesAndPointsHaveSameStartTangents();
		UE_LOG(LogTemp, Log, TEXT("Road splines start tangents are coincident with the tangents of spline points: %s."), *FString(roadSplinesStartTangentsMatchSplinePoints ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the start tangents of road splines should be coincident with the spline points tangents."), roadSplinesStartTangentsMatchSplinePoints);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorRoadSplinesStartTangentsAreTheSameAsSplinePointsAtSpawningTest, "ProjectR.TrackGenerator Tests.Unit.006: Road splines start tangents are the same as spline points at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorRoadSplinesStartTangentsAreTheSameAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesStartTangentsCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRoadSplinesEndTangentsCommand, FAutomationTestBase*, test);

bool FCheckRoadSplinesEndTangentsCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesEndTangentsMatchNextSplinePoints = testGenerator->roadSplinesAndPointsHaveSameEndTangents();
		UE_LOG(LogTemp, Log, TEXT("Road splines end tangents are coincident with the tangents of next spline points: %s."), *FString(roadSplinesEndTangentsMatchNextSplinePoints ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the end tangents of road splines should be coincident with the next spline points tangents."), roadSplinesEndTangentsMatchNextSplinePoints);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorRoadSplinesEndTangentsAreTheSameAsNextSplinePointsAtSpawningTest, "ProjectR.TrackGenerator Tests.Unit.007: Road splines end tangents are the same as next spline points at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorRoadSplinesEndTangentsAreTheSameAsNextSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesEndTangentsCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRoadSplinesMeshesCommand, FAutomationTestBase*, test);

bool FCheckRoadSplinesMeshesCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesHaveMeshesSet = testGenerator->roadSplinesHaveMeshesSet();
		UE_LOG(LogTemp, Log, TEXT("Road splines meshes are set: %s."), *FString(roadSplinesHaveMeshesSet ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the road splines meshes should be set."), roadSplinesHaveMeshesSet);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorRoadSplinesMeshesAreSetAtSpawningTest, "ProjectR.TrackGenerator Tests.Unit.008: Road splines meshes are set at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorRoadSplinesMeshesAreSetAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesMeshesCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRoadSplinesMeshesAreRoadMeshCommand, FAutomationTestBase*, test);

bool FCheckRoadSplinesMeshesAreRoadMeshCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesHaveMeshesSetAsRoadMesh = testGenerator->roadSplinesMeshesAreRoadMesh();
		UE_LOG(LogTemp, Log, TEXT("Road splines meshes are the road mesh: %s."), *FString(roadSplinesHaveMeshesSetAsRoadMesh ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the road splines meshes should be the road mesh."), roadSplinesHaveMeshesSetAsRoadMesh);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorRoadSplinesMeshesAreTheRoadMeshAtSpawningTest, "ProjectR.TrackGenerator Tests.Unit.009: Road splines meshes are the road mesh at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorRoadSplinesMeshesAreTheRoadMeshAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesMeshesAreRoadMeshCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSplineMagnetSplinesQuantityCommand, FAutomationTestBase*, test);

bool FCheckSplineMagnetSplinesQuantityCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool splineHasSameNumberOfMagnetSplinesAsSplinePoints = testGenerator->magnetSplinesQuantitySameAsSplinePoints();
		UE_LOG(LogTemp, Log, TEXT("Has the same amount of spline points as magnet splines: %s."), *FString(splineHasSameNumberOfMagnetSplinesAsSplinePoints ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the spline should have the same amount of magnet splines as spline points."), splineHasSameNumberOfMagnetSplinesAsSplinePoints);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorHasTheSameAmountOfMagnetSplinesAsSplinePointsAtSpawningTest, "ProjectR.TrackGenerator Tests.Unit.010: Has the same amount of magnet splines as spline points at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorHasTheSameAmountOfMagnetSplinesAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplineMagnetSplinesQuantityCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRoadSplinesCollisionEnabledCommand, FAutomationTestBase*, test);

bool FCheckRoadSplinesCollisionEnabledCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesHaveCollisionEnabledSetToQueryAndPhysics = testGenerator->roadSplinesHaveCollisionEnabledSetToQueryAndPhysics();
		UE_LOG(LogTemp, Log, TEXT("Road splines have collision enabled set to query and physics: %s."), *FString(roadSplinesHaveCollisionEnabledSetToQueryAndPhysics ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, Road splines should have collision enabled set to query and physics."), roadSplinesHaveCollisionEnabledSetToQueryAndPhysics);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMeshesHaveCollisionEnabledAtSpawningTest, "ProjectR.TrackGenerator Tests.Unit.011: Meshes have collision enabled at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMeshesHaveCollisionEnabledAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesCollisionEnabledCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRoadSplinesCollisionObjectTypeCommand, FAutomationTestBase*, test);

bool FCheckRoadSplinesCollisionObjectTypeCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesHaveCollisionObjectToWorldStatic = testGenerator->roadSplinesHaveCollisionObjectToWorldStatic();
		UE_LOG(LogTemp, Log, TEXT("Road splines have collision object type of world static: %s."), *FString(roadSplinesHaveCollisionObjectToWorldStatic ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, Road splines should have collision object type of world static."), roadSplinesHaveCollisionObjectToWorldStatic);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMeshesHaveCollisionObjectTypeWorldStaticAtSpawningTest, "ProjectR.TrackGenerator Tests.Unit.012: Meshes have collision object type world static at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMeshesHaveCollisionObjectTypeWorldStaticAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesCollisionObjectTypeCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRoadSplinesAttachToRootCommand, FAutomationTestBase*, test);

bool FCheckRoadSplinesAttachToRootCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesAreAttachedToRoot = testGenerator->roadSplinesAreAttachedToRoot();
		UE_LOG(LogTemp, Log, TEXT("Road splines are attached to root component: %s."), *FString(roadSplinesAreAttachedToRoot ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, Road splines should be attached to root component."), roadSplinesAreAttachedToRoot);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMeshesAreAttachedToRootAtSpawningTest, "ProjectR.TrackGenerator Tests.Unit.013: Meshes are attached to root at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMeshesAreAttachedToRootAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesAttachToRootCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRoadSplinesMobilityCommand, FAutomationTestBase*, test);

bool FCheckRoadSplinesMobilityCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesMobilitySameAsRoot = testGenerator->roadSplinesMobilitySameAsRoot();
		UE_LOG(LogTemp, Log, TEXT("Road splines have the same mobility as the root component: %s."), *FString(roadSplinesMobilitySameAsRoot ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, Road splines should have the same mobility as the root component."), roadSplinesMobilitySameAsRoot);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMeshesHaveSameMobilityAsRootAtSpawningTest, "ProjectR.TrackGenerator Tests.Unit.014: Meshes have same mobility as root at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMeshesHaveSameMobilityAsRootAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRoadSplinesMobilityCommand(this));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineComponentLoopsTest, "ProjectR.TrackGenerator Tests.Unit.015: Spline component loops", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorSplineComponentLoopsTest::RunTest(const FString& Parameters)
{
	ATrackGeneratorMOCK* testGenerator = NewObject<ATrackGeneratorMOCK>();
	{
		TestTrue(TEXT("The track generator spline component should loop, these are race tracks."), testGenerator->isSplineComponentLooping());
	}

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetSplinesMobilityCommand, FAutomationTestBase*, test);

bool FCheckMagnetSplinesMobilityCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetSplinesMobilitySameAsRoadSplines = testGenerator->magnetSplinesMobilitySameAsRoadSplines();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines have the same mobility as road splines: %s."), *FString(magnetSplinesMobilitySameAsRoadSplines ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, magnet splines should have the same mobility as road splines."), magnetSplinesMobilitySameAsRoadSplines);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesHaveTheSameMobilityAsRoadSplinesAtSpawningTest, "ProjectR.TrackGenerator Tests.Unit.016: Magnet splines have the same mobility as road splines at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetSplinesHaveTheSameMobilityAsRoadSplinesAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesMobilityCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetSplinesAttachToRoadSplinesCommand, FAutomationTestBase*, test);

bool FCheckMagnetSplinesAttachToRoadSplinesCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetSplinesAreAttachedToRoadSplines = testGenerator->magnetSplinesAreAttachedToRoadSplines();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines are attached to road splines: %s."), *FString(magnetSplinesAreAttachedToRoadSplines ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, magnet splines should be attached to road splines."), magnetSplinesAreAttachedToRoadSplines);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesAreAttachedToRoadSplinesAtSpawningTest, "ProjectR.TrackGenerator Tests.Unit.017: Magnet splines are attached to road splines at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetSplinesAreAttachedToRoadSplinesAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesAttachToRoadSplinesCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetSplinesOnTopRoadSplinesCommand, FAutomationTestBase*, test);

bool FCheckMagnetSplinesOnTopRoadSplinesCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetSplinesOnTopOfRoadSplines = testGenerator->magnetSplinesOnTopOfRoadSplines();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines are on top of road splines: %s."), *FString(magnetSplinesOnTopOfRoadSplines ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, magnet splines should be on top of road splines."), magnetSplinesOnTopOfRoadSplines);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesAreOnTopOfRoadSplinesAtSpawningTest, "ProjectR.TrackGenerator Tests.Unit.018: Magnet splines are on top of road splines at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetSplinesAreOnTopOfRoadSplinesAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesOnTopRoadSplinesCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetSplinesTangentsCommand, FAutomationTestBase*, test);

bool FCheckMagnetSplinesTangentsCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetSplinesAndPointsHaveSameTangents = testGenerator->magnetSplinesAndPointsHaveSameTangents();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines tangents are coincident with the tangents of spline points: %s."), *FString(magnetSplinesAndPointsHaveSameTangents ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the tangents of magnet splines should be coincident with the spline points tangents."), magnetSplinesAndPointsHaveSameTangents);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesTangentsAreTheSameAsSplinePointsAtSpawningTest, "ProjectR.TrackGenerator Tests.Unit.019: Magnet splines tangents are the same as spline points at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetSplinesTangentsAreTheSameAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesTangentsCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetSplinesMeshesCommand, FAutomationTestBase*, test);

bool FCheckMagnetSplinesMeshesCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetSplinesHaveMeshesSet = testGenerator->magnetSplinesHaveMeshesSet();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines meshes are set: %s."), *FString(magnetSplinesHaveMeshesSet ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the magnet splines meshes should be set."), magnetSplinesHaveMeshesSet);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesMeshesAreSetAtSpawningTest, "ProjectR.TrackGenerator Tests.Unit.020: Magnet splines meshes are set at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetSplinesMeshesAreSetAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesMeshesCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetSplinesVisibilityCommand, FAutomationTestBase*, test);

bool FCheckMagnetSplinesVisibilityCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetSplinesAreHiddenInGame = testGenerator->magnetSplinesAreHiddenInGame();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines are hidden in game: %s."), *FString(magnetSplinesAreHiddenInGame ? "true" : "false"));


		test->TestTrue(TEXT("The magnet splines should be set hidden in game."), magnetSplinesAreHiddenInGame);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesAreHiddenInGameTest, "ProjectR.TrackGenerator Tests.Unit.021: Magnet splines are hidden in game", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetSplinesAreHiddenInGameTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesVisibilityCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetSplinesCollisionResponseCommand, FAutomationTestBase*, test);

bool FCheckMagnetSplinesCollisionResponseCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool collisionEnabledToQueryOnlyOnMagnetSplines = testGenerator->collisionEnabledToQueryOnlyOnMagnetSplines();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines have collision enabled: %s."), *FString(collisionEnabledToQueryOnlyOnMagnetSplines ? "true" : "false"));


		test->TestTrue(TEXT("The magnet splines should have collision enabled."), collisionEnabledToQueryOnlyOnMagnetSplines);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesHaveCollisionEnabledToQueryOnlyTest, "ProjectR.TrackGenerator Tests.Unit.022: Magnet splines have collision enabled to query only", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetSplinesHaveCollisionEnabledToQueryOnlyTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesCollisionResponseCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetSplinesResponseToPawnChannelCommand, FAutomationTestBase*, test);

bool FCheckMagnetSplinesResponseToPawnChannelCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetSplinesOverlapWithPawnChannel = testGenerator->magnetSplinesOverlapWithPawnChannel();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines overlap with the pawn channel: %s."), *FString(magnetSplinesOverlapWithPawnChannel ? "true" : "false"));


		test->TestTrue(TEXT("The magnet splines should overlap with the pawn channel."), magnetSplinesOverlapWithPawnChannel);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesOverlapWithPawnChannelTest, "ProjectR.TrackGenerator Tests.Unit.023: Magnet splines overlap with pawn channel", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetSplinesOverlapWithPawnChannelTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesResponseToPawnChannelCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetSplinesGenerateOverlapEventsCommand, FAutomationTestBase*, test);

bool FCheckMagnetSplinesGenerateOverlapEventsCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetSplinesGenerateOverlapEvents = testGenerator->magnetSplinesGenerateOverlapEvents();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines generate overlap events: %s."), *FString(magnetSplinesGenerateOverlapEvents ? "true" : "false"));


		test->TestTrue(TEXT("The magnet splines should generate overlap events."), magnetSplinesGenerateOverlapEvents);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesGenerateOverlapEventsTest, "ProjectR.TrackGenerator Tests.Unit.024: Magnet splines generate overlap events", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetSplinesGenerateOverlapEventsTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetSplinesGenerateOverlapEventsCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckComponentsSmoothInterpolationCommand, FAutomationTestBase*, test);

bool FCheckComponentsSmoothInterpolationCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool componentsHaveSmoothInterpolation = testGenerator->componentsHaveSmoothInterpolation();
		UE_LOG(LogTemp, Log, TEXT("Components have smooth interpolation: %s."), *FString(componentsHaveSmoothInterpolation ? "true" : "false"));


		test->TestTrue(TEXT("The components should have smooth interpolation."), componentsHaveSmoothInterpolation);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineMeshComponentsHaveSmoothInterpolationEnabledTest, "ProjectR.TrackGenerator Tests.Unit.025: Spline mesh components have smooth interpolation enabled", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorSplineMeshComponentsHaveSmoothInterpolationEnabledTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckComponentsSmoothInterpolationCommand(this));

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorGeneratesOverlapEventsWhenSpawnedTest, "ProjectR.TrackGenerator Tests.Unit.026: Generates overlap events when spawned", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorGeneratesOverlapEventsWhenSpawnedTest::RunTest(const FString& Parameters)
{
	ATrackGenerator* testGenerator = NewObject<ATrackGenerator>();
	{
		TestTrue(TEXT("The track generator should generate overlap events when spawned."), testGenerator->bGenerateOverlapEventsDuringLevelStreaming);
	}

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckTrackSectionsArrayQuantityAdjustedToNumberOfSplinePointsCommand, FAutomationTestBase*, test);

bool FCheckTrackSectionsArrayQuantityAdjustedToNumberOfSplinePointsCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool sameAmountOfTrackSectionsThanSplinePoints = testGenerator->sameAmountOfTrackSectionsThanSplinePoints();
		UE_LOG(LogTemp, Log, TEXT("The track sections array has the same number of elements as the number of spline points: %s."), *FString(sameAmountOfTrackSectionsThanSplinePoints ? "true" : "false"));


		test->TestTrue(TEXT("The track sections array should have the same number of elements as the number of spline points."), sameAmountOfTrackSectionsThanSplinePoints);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorTrackSectionsQuantityMatchesSplinePointsNumberTest, "ProjectR.TrackGenerator Tests.Unit.027: Track sections quantity is adjusted to the number of spline points", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorTrackSectionsQuantityMatchesSplinePointsNumberTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckTrackSectionsArrayQuantityAdjustedToNumberOfSplinePointsCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FSpawnTrackGeneratorInEditorWorldRollSplineComponentsCommand, float, rollValue);

bool FSpawnTrackGeneratorInEditorWorldRollSplineComponentsCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}

	UWorld* testWorld = GEditor->GetEditorWorldContext().World();

	ATrackGeneratorMOCK* testGenerator = testWorld->SpawnActor<ATrackGeneratorMOCK>(ATrackGeneratorMOCK::StaticClass());

	testGenerator->rollSplines(rollValue);

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckComponentsRollCommand, float, rollValue, FAutomationTestBase*, test);

bool FCheckComponentsRollCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{
		bool componentsRollMatchSettedRoll = testGenerator->splineMeshComponentsRollIs(rollValue);
		UE_LOG(LogTemp, Log, TEXT("Components match setted roll: %s."), *FString(componentsRollMatchSettedRoll ? "true" : "false"));

		test->TestTrue(TEXT("The components should have their roll matching the one set."), componentsRollMatchSettedRoll);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineMeshComponentsRollAfterSettingRollInEditorTest, "ProjectR.TrackGenerator Tests.Unit.028: Spline mesh components modify their roll when setting it", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorSplineMeshComponentsRollAfterSettingRollInEditorTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	float rollValue = 30.0f;
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldRollSplineComponentsCommand(rollValue));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckComponentsRollCommand(rollValue, this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FSpawnTrackGeneratorInEditorWorldWidenSplineComponentsCommand, float, widthValue);

bool FSpawnTrackGeneratorInEditorWorldWidenSplineComponentsCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}

	UWorld* testWorld = GEditor->GetEditorWorldContext().World();

	ATrackGeneratorMOCK* testGenerator = testWorld->SpawnActor<ATrackGeneratorMOCK>(ATrackGeneratorMOCK::StaticClass());

	testGenerator->WidenSplines(widthValue);

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckComponentsWidthCommand, float, widthValue, FAutomationTestBase*, test);

bool FCheckComponentsWidthCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{
		bool componentsWidthMatchSettedWidth = testGenerator->splineMeshComponentsWidthIs(widthValue);
		UE_LOG(LogTemp, Log, TEXT("Components match setted width: %s."), *FString(componentsWidthMatchSettedWidth ? "true" : "false"));

		test->TestTrue(TEXT("The components should have their width matching the one set."), componentsWidthMatchSettedWidth);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineMeshComponentsWidenAfterSettingWidenInEditorTest, "ProjectR.TrackGenerator Tests.Unit.029: Spline mesh components modify their width when setting it", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorSplineMeshComponentsWidenAfterSettingWidenInEditorTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	float widthValue = 30.0f;
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldWidenSplineComponentsCommand(widthValue));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckComponentsWidthCommand(widthValue, this));

	return true;
}



//allow to change width for each spline mesh.
//(when a custom mesh for magnet spline is already made) set location of magnet spline same as spline mesh,
// attach and elevate the same amount as the bound of mesh (saved in constructor) multiplied by the scale (gotten in on construction).









#endif //WITH_DEV_AUTOMATION_TESTS