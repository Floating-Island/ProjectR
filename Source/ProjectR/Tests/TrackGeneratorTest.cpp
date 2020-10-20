// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackGeneratorTest.h"

#include "Track/TrackGenerator.h"
#include "Mocks/TrackGeneratorMOCK.h"
#include "Mocks/JetMOCK.h"

#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Editor.h"
#include "../../../../../Program Files/Epic Games/UE_4.25/Engine/Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Engine.h"



#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.Unit.ClassToTest.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorShouldntBeNullWhenInstantiatedTest, "ProjectR.Unit.TrackGeneratorTest.ATrackGeneratorShouldntBeNullWhenInstantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorShouldntBeNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ATrackGenerator* testGenerator = NewObject<ATrackGenerator>();
	{
		TestNotNull(TEXT("The track generator shouldn't be null when instantiated."), testGenerator);
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorShouldHaveASplineComponentTest, "ProjectR.Unit.TrackGeneratorTest.ATrackGeneratorShouldHaveASplineComponent", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorShouldHaveASplineComponentTest::RunTest(const FString& Parameters)
{
	ATrackGeneratorMOCK* testGenerator = NewObject<ATrackGeneratorMOCK>();
	{
		TestTrue(TEXT("The track generator should have a spline component."), testGenerator->hasSplineComponent());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineComponentShouldBeTheRootComponentTest, "ProjectR.Unit.TrackGeneratorTest.ATrackGeneratorSplineComponentShouldBeTheRootComponent", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorSplineComponentShouldBeTheRootComponentTest::RunTest(const FString& Parameters)
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


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSplineMeshesQuantityCommand, FAutomationTestBase*, test);

bool FCheckSplineMeshesQuantityCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{
		int32 splineMeshesQuantity = testGenerator->splineMeshesQuantity();
		int32 splinePointsQuantity = testGenerator->splinePointsQuantity();
		bool sameAmountOfSplinePointsAsSplineMeshes = splineMeshesQuantity == splinePointsQuantity;//splines always have start and end points at the beginning...
		UE_LOG(LogTemp, Log, TEXT("Spline points quantity in generator: %d."), splinePointsQuantity);
		UE_LOG(LogTemp, Log, TEXT("Spline meshes quantity in generator: %d."), splineMeshesQuantity);
		UE_LOG(LogTemp, Log, TEXT("Spline meshes quantity is coincident with number of spline points: %s."), *FString(sameAmountOfSplinePointsAsSplineMeshes ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the number of spline meshes should be coincident with the spline points quantity."), sameAmountOfSplinePointsAsSplineMeshes);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineMeshesQuantityShouldBeTheSameAsSplinePointsAtSpawningTest, "ProjectR.Unit.TrackGeneratorTest.SplineMeshesQuantityShouldBeTheSameAsSplinePointsAtSpawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorSplineMeshesQuantityShouldBeTheSameAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplineMeshesQuantityCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSplineMeshesStartPositionsCommand, FAutomationTestBase*, test);

bool FCheckSplineMeshesStartPositionsCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool splineMeshesStartPositionsMatchSplinePoints = testGenerator->MeshesAndPointsHaveSameStartPositions();
		UE_LOG(LogTemp, Log, TEXT("Spline meshes start positions are coincident with the positions of spline points: %s."), *FString(splineMeshesStartPositionsMatchSplinePoints ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the start positions of spline meshes should be coincident with the spline points positions."), splineMeshesStartPositionsMatchSplinePoints);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineMeshesStartPositionsShouldBeTheSameAsSplinePointsAtSpawningTest, "ProjectR.Unit.TrackGeneratorTest.SplineMeshesStartPositionsShouldBeTheSameAsSplinePointsAtSpawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorSplineMeshesStartPositionsShouldBeTheSameAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplineMeshesStartPositionsCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSplineMeshesEndPositionsCommand, FAutomationTestBase*, test);

bool FCheckSplineMeshesEndPositionsCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool splineMeshesEndPositionsMatchSplinePoints = testGenerator->MeshesAndPointsHaveSameEndPositions();
		UE_LOG(LogTemp, Log, TEXT("Spline meshes end positions are coincident with the positions of next spline points: %s."), *FString(splineMeshesEndPositionsMatchSplinePoints ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the end positions of spline meshes should be coincident with the next spline points positions."), splineMeshesEndPositionsMatchSplinePoints);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineMeshesEndPositionsShouldBeTheSameAsNextSplinePointsAtSpawningTest, "ProjectR.Unit.TrackGeneratorTest.SplineMeshesEndPositionsShouldBeTheSameAsNextSplinePointsAtSpawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorSplineMeshesEndPositionsShouldBeTheSameAsNextSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplineMeshesEndPositionsCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSplineMeshesStartTangentsCommand, FAutomationTestBase*, test);

bool FCheckSplineMeshesStartTangentsCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool splineMeshesStartTangentsMatchSplinePoints = testGenerator->MeshesAndPointsHaveSameStartTangents();
		UE_LOG(LogTemp, Log, TEXT("Spline meshes start tangents are coincident with the tangents of spline points: %s."), *FString(splineMeshesStartTangentsMatchSplinePoints ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the start tangents of spline meshes should be coincident with the spline points tangents."), splineMeshesStartTangentsMatchSplinePoints);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineMeshesStartTangentsShouldBeTheSameAsSplinePointsAtSpawningTest, "ProjectR.Unit.TrackGeneratorTest.SplineMeshesStartTangentsShouldBeTheSameAsSplinePointsAtSpawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorSplineMeshesStartTangentsShouldBeTheSameAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplineMeshesStartTangentsCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSplineMeshesEndTangentsCommand, FAutomationTestBase*, test);

bool FCheckSplineMeshesEndTangentsCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool splineMeshesEndTangentsMatchNextSplinePoints = testGenerator->MeshesAndPointsHaveSameEndTangents();
		UE_LOG(LogTemp, Log, TEXT("Spline meshes end tangents are coincident with the tangents of next spline points: %s."), *FString(splineMeshesEndTangentsMatchNextSplinePoints ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the end tangents of spline meshes should be coincident with the next spline points tangents."), splineMeshesEndTangentsMatchNextSplinePoints);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineMeshesEndTangentsShouldBeTheSameAsNextSplinePointsAtSpawningTest, "ProjectR.Unit.TrackGeneratorTest.SplineMeshesEndTangentsShouldBeTheSameAsNextSplinePointsAtSpawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorSplineMeshesEndTangentsShouldBeTheSameAsNextSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplineMeshesEndTangentsCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSplineMeshesMeshesCommand, FAutomationTestBase*, test);

bool FCheckSplineMeshesMeshesCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool splineMeshesHaveMeshesSet = testGenerator->splineMeshesHaveMeshesSet();
		UE_LOG(LogTemp, Log, TEXT("Spline meshes meshes are set: %s."), *FString(splineMeshesHaveMeshesSet ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the spline meshes meshes should be set."), splineMeshesHaveMeshesSet);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineMeshesMeshesShouldBeSetAtSpawningTest, "ProjectR.Unit.TrackGeneratorTest.SplineMeshesMeshesShouldBeSetAtSpawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorSplineMeshesMeshesShouldBeSetAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplineMeshesMeshesCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSplineMeshesMeshesAreRoadMeshCommand, FAutomationTestBase*, test);

bool FCheckSplineMeshesMeshesAreRoadMeshCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool splineMeshesHaveMeshesSetAsRoadMesh = testGenerator->splineMeshesMeshesAreRoadMesh();
		UE_LOG(LogTemp, Log, TEXT("Spline meshes meshes are the road mesh: %s."), *FString(splineMeshesHaveMeshesSetAsRoadMesh ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the spline meshes meshes should be the road mesh."), splineMeshesHaveMeshesSetAsRoadMesh);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineMeshesMeshesShouldBeTheRoadMeshAtSpawningTest, "ProjectR.Unit.TrackGeneratorTest.SplineMeshesMeshesShouldBeTheRoadMeshAtSpawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorSplineMeshesMeshesShouldBeTheRoadMeshAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplineMeshesMeshesAreRoadMeshCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSplineMagnetBoxesQuantityCommand, FAutomationTestBase*, test);

bool FCheckSplineMagnetBoxesQuantityCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool splineHasSameNumberOfMagnetBoxesAsSplinePoints = testGenerator->MagnetBoxesQuantitySameAsSplinePoints();
		UE_LOG(LogTemp, Log, TEXT("Has the same amount of spline points as magnet boxes: %s."), *FString(splineHasSameNumberOfMagnetBoxesAsSplinePoints ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the spline should have the same amount of magnet boxes as spline points."), splineHasSameNumberOfMagnetBoxesAsSplinePoints);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorShouldHaveSameAmountOfMagnetBoxesAsSplinePointsAtSpawningTest, "ProjectR.Unit.TrackGeneratorTest.ShouldHaveSameAmountOfMagnetBoxesAsSplinePointsAtSpawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorShouldHaveSameAmountOfMagnetBoxesAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplineMagnetBoxesQuantityCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSplineMeshesCollisionEnabledCommand, FAutomationTestBase*, test);

bool FCheckSplineMeshesCollisionEnabledCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool splineMeshesHaveCollisionEnabledSetToQueryAndPhysics = testGenerator->splineMeshesHaveCollisionEnabledSetToQueryAndPhysics();
		UE_LOG(LogTemp, Log, TEXT("Spline meshes have collision enabled set to query and physics: %s."), *FString(splineMeshesHaveCollisionEnabledSetToQueryAndPhysics ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, Spline meshes should have collision enabled set to query and physics."), splineMeshesHaveCollisionEnabledSetToQueryAndPhysics);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMeshesShouldHaveCollisionEnabledAtSpawningTest, "ProjectR.Unit.TrackGeneratorTest.MeshesShouldHaveCollisionEnabledAtSpawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMeshesShouldHaveCollisionEnabledAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplineMeshesCollisionEnabledCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSplineMeshesCollisionObjectTypeCommand, FAutomationTestBase*, test);

bool FCheckSplineMeshesCollisionObjectTypeCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool splineMeshesHaveCollisionObjectToWorldStatic = testGenerator->splineMeshesHaveCollisionObjectToWorldStatic();
		UE_LOG(LogTemp, Log, TEXT("Spline meshes have collision object type of world static: %s."), *FString(splineMeshesHaveCollisionObjectToWorldStatic ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, Spline meshes should have collision object type of world static."), splineMeshesHaveCollisionObjectToWorldStatic);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMeshesShouldHaveCollisionObjectTypeWorldStaticAtSpawningTest, "ProjectR.Unit.TrackGeneratorTest.MeshesShouldHaveCollisionObjectTypeWorldStaticAtSpawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMeshesShouldHaveCollisionObjectTypeWorldStaticAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplineMeshesCollisionObjectTypeCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSplineMeshesAttachToRootCommand, FAutomationTestBase*, test);

bool FCheckSplineMeshesAttachToRootCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool splineMeshesAreAttachedToRoot = testGenerator->splineMeshesAreAttachedToRoot();
		UE_LOG(LogTemp, Log, TEXT("Spline meshes are attached to root component: %s."), *FString(splineMeshesAreAttachedToRoot ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, Spline meshes should be attached to root component."), splineMeshesAreAttachedToRoot);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMeshesShouldBeAttachedToRootAtSpawningTest, "ProjectR.Unit.TrackGeneratorTest.MeshesShouldBeAttachedToRootAtSpawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMeshesShouldBeAttachedToRootAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplineMeshesAttachToRootCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSplineMeshesMobilityCommand, FAutomationTestBase*, test);

bool FCheckSplineMeshesMobilityCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool splineMeshesMobilitySameAsRoot = testGenerator->splineMeshesMobilitySameAsRoot();
		UE_LOG(LogTemp, Log, TEXT("Spline meshes have the same mobility as the root component: %s."), *FString(splineMeshesMobilitySameAsRoot ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, Spline meshes should have the same mobility as the root component."), splineMeshesMobilitySameAsRoot);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMeshesShouldHaveSameMobilityAsRootAtSpawningTest, "ProjectR.Unit.TrackGeneratorTest.MeshesShouldHaveSameMobilityAsRootAtSpawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMeshesShouldHaveSameMobilityAsRootAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplineMeshesMobilityCommand(this));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineComponentShouldLoopTest, "ProjectR.Unit.TrackGeneratorTest.SplineComponentShouldLoop", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorSplineComponentShouldLoopTest::RunTest(const FString& Parameters)
{
	ATrackGeneratorMOCK* testGenerator = NewObject<ATrackGeneratorMOCK>();
	{
		TestTrue(TEXT("The track generator spline component should loop, I'm doing race tracks."), testGenerator->isSplineComponentLooping());
	}

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetBoxesMobilityCommand, FAutomationTestBase*, test);

bool FCheckMagnetBoxesMobilityCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetBoxesMobilitySameAsSplineMeshes = testGenerator->magnetBoxesMobilitySameAsSplineMeshes();
		UE_LOG(LogTemp, Log, TEXT("Magnet boxes have the same mobility as spline meshes: %s."), *FString(magnetBoxesMobilitySameAsSplineMeshes ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, magnet boxes should have the same mobility as spline meshes."), magnetBoxesMobilitySameAsSplineMeshes);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetBoxesShouldHaveSameMobilityAsSplineMeshesAtSpawningTest, "ProjectR.Unit.TrackGeneratorTest.MagnetBoxesShouldHaveSameMobilityAsSplineMeshesAtSpawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetBoxesShouldHaveSameMobilityAsSplineMeshesAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetBoxesMobilityCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetBoxesAttachToSplineMeshesCommand, FAutomationTestBase*, test);

bool FCheckMagnetBoxesAttachToSplineMeshesCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetBoxesAreAttachedToSplineMeshes = testGenerator->magnetBoxesAreAttachedToSplineMeshes();
		UE_LOG(LogTemp, Log, TEXT("Magnet boxes are attached to spline meshes: %s."), *FString(magnetBoxesAreAttachedToSplineMeshes ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, magnet boxes should be attached to spline meshes."), magnetBoxesAreAttachedToSplineMeshes);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetBoxesShouldBeAttachedToSplineMeshesAtSpawningTest, "ProjectR.Unit.TrackGeneratorTest.MagnetBoxesShouldBeAttachedToSplineMeshesAtSpawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetBoxesShouldBeAttachedToSplineMeshesAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetBoxesAttachToSplineMeshesCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetBoxesOnTopSplineMeshesCommand, FAutomationTestBase*, test);

bool FCheckMagnetBoxesOnTopSplineMeshesCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetBoxesOnTopOfSplineMeshes = testGenerator->magnetBoxesOnTopOfSplineMeshes();
		UE_LOG(LogTemp, Log, TEXT("Magnet boxes are on top of spline meshes: %s."), *FString(magnetBoxesOnTopOfSplineMeshes ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, magnet boxes should be on top of spline meshes."), magnetBoxesOnTopOfSplineMeshes);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetBoxesShouldBeOnTopOfSplineMeshesAtSpawningTest, "ProjectR.Unit.TrackGeneratorTest.MagnetBoxesShouldBeOnTopOfSplineMeshesAtSpawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetBoxesShouldBeOnTopOfSplineMeshesAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetBoxesOnTopSplineMeshesCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetBoxesTangentsCommand, FAutomationTestBase*, test);

bool FCheckMagnetBoxesTangentsCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetBoxesAndPointsHaveSameTangents = testGenerator->magnetBoxesAndPointsHaveSameTangents();
		UE_LOG(LogTemp, Log, TEXT("Magnet boxes tangents are coincident with the tangents of spline points: %s."), *FString(magnetBoxesAndPointsHaveSameTangents ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the tangents of magnet boxes should be coincident with the spline points tangents."), magnetBoxesAndPointsHaveSameTangents);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetBoxesTangentsShouldBeTheSameAsSplinePointsAtSpawningTest, "ProjectR.Unit.TrackGeneratorTest.MagnetBoxesTangentsShouldBeTheSameAsSplinePointsAtSpawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetBoxesTangentsShouldBeTheSameAsSplinePointsAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetBoxesTangentsCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetBoxesMeshesCommand, FAutomationTestBase*, test);

bool FCheckMagnetBoxesMeshesCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetBoxesHaveMeshesSet = testGenerator->magnetBoxesHaveMeshesSet();
		UE_LOG(LogTemp, Log, TEXT("Magnet boxes meshes are set: %s."), *FString(magnetBoxesHaveMeshesSet ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the magnet boxes meshes should be set."), magnetBoxesHaveMeshesSet);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetBoxesMeshesShouldBeSetAtSpawningTest, "ProjectR.Unit.TrackGeneratorTest.MagnetBoxesMeshesShouldBeSetAtSpawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetBoxesMeshesShouldBeSetAtSpawningTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetBoxesMeshesCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetBoxesVisibilityCommand, FAutomationTestBase*, test);

bool FCheckMagnetBoxesVisibilityCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetBoxesAreHiddenInGame = testGenerator->magnetBoxesAreHiddenInGame();
		UE_LOG(LogTemp, Log, TEXT("Magnet boxes are hidden in game: %s."), *FString(magnetBoxesAreHiddenInGame ? "true" : "false"));


		test->TestTrue(TEXT("The magnet boxes should be set hidden in game."), magnetBoxesAreHiddenInGame);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetBoxesShouldBeHiddenInGameTest, "ProjectR.Unit.TrackGeneratorTest.MagnetBoxesShouldBeHiddenInGame", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetBoxesShouldBeHiddenInGameTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetBoxesVisibilityCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetBoxesCollisionResponseCommand, FAutomationTestBase*, test);

bool FCheckMagnetBoxesCollisionResponseCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool collisionEnabledToQueryOnlyOnMagnetBoxes = testGenerator->collisionEnabledToQueryOnlyOnMagnetBoxes();
		UE_LOG(LogTemp, Log, TEXT("Magnet boxes have collision enabled: %s."), *FString(collisionEnabledToQueryOnlyOnMagnetBoxes ? "true" : "false"));


		test->TestTrue(TEXT("The magnet boxes should have collision enabled."), collisionEnabledToQueryOnlyOnMagnetBoxes);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetBoxesShouldHaveCollisionEnabledToQueryOnlyTest, "ProjectR.Unit.TrackGeneratorTest.MagnetBoxesShouldHaveCollisionEnabledToQueryOnly", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetBoxesShouldHaveCollisionEnabledToQueryOnlyTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetBoxesCollisionResponseCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetBoxesResponseToPawnChannelCommand, FAutomationTestBase*, test);

bool FCheckMagnetBoxesResponseToPawnChannelCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetBoxesOverlapWithPawnChannel = testGenerator->magnetBoxesOverlapWithPawnChannel();
		UE_LOG(LogTemp, Log, TEXT("Magnet boxes overlap with the pawn channel: %s."), *FString(magnetBoxesOverlapWithPawnChannel ? "true" : "false"));


		test->TestTrue(TEXT("The magnet boxes should overlap with the pawn channel."), magnetBoxesOverlapWithPawnChannel);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetBoxesShouldOverlapWithPawnChannelTest, "ProjectR.Unit.TrackGeneratorTest.MagnetBoxesShouldOverlapWithPawnChannel", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetBoxesShouldOverlapWithPawnChannelTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetBoxesResponseToPawnChannelCommand(this));

	return true;
}






IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMeshCollisionTypeShouldBePawnTest, "ProjectR.Unit.TrackGeneratorTest.AJetMeshCollisionTypeShouldBePawn", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetMeshCollisionTypeShouldBePawnTest::RunTest(const FString& Parameters)
{
	AJetMOCK* testJet = NewObject<AJetMOCK>();
	{
		TestTrue(TEXT("The jet collision object type should be pawn."), testJet->meshCollisionIsPawn());
	}

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMagnetBoxesGenerateOverlapEventsCommand, FAutomationTestBase*, test);

bool FCheckMagnetBoxesGenerateOverlapEventsCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetBoxesGenerateOverlapEvents = testGenerator->magnetBoxesGenerateOverlapEvents();
		UE_LOG(LogTemp, Log, TEXT("Magnet boxes generate overlap events: %s."), *FString(magnetBoxesGenerateOverlapEvents ? "true" : "false"));


		test->TestTrue(TEXT("The magnet boxes should generate overlap events."), magnetBoxesGenerateOverlapEvents);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetBoxesShouldGenerateOverlapEventsTest, "ProjectR.Unit.TrackGeneratorTest.MagnetBoxesShouldGenerateOverlapEvents", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorMagnetBoxesShouldGenerateOverlapEventsTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMagnetBoxesGenerateOverlapEventsCommand(this));

	return true;
}






//enable collision on the magnet box (query only).
//make the magnet box ignore all channels.
//make the magnet box respond to pawn overlap (jet overlaps too, the test is in the track tests).
//make the magnet box generate overlap events.
//make the magnet box broadcast on begin overlap and on end overlap events (it's automatic once we generate overlap events).
//make a track manager to catch those events, add the overlapped pawns to a owning set and every frame travel the set and magnetize pawns this way:
//1) get the jet location.
//2) search along the spline the nearest point to the jet location.
//3) trace a line from the jet towards the nearest spline location (it will hit the spline mesh surface).
//4) get the normal of that surface (from the hit result).
//5) cancel gravity.
//6) apply gravity contrary to the surface normal (it needs to pull), like how it's done in the track.


//allow to change roll to spline meshes. Make the magnet box attached to that roll (roll after the magnet box has been attached).
//set location of magnet box same as spline mesh, attach and elevate the same amount as the bound of mesh (saved in constructor) multiplied by the scale (gotten in on construction).









#endif //WITH_DEV_AUTOMATION_TESTS