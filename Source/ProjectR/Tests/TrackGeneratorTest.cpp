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







#endif //WITH_DEV_AUTOMATION_TESTS