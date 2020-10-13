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


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckSplineMeshesCreatedCommand, int, tickCounter, int, tickLimit, FAutomationTestBase*, test);

bool FCheckSplineMeshesCreatedCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{
		int32 initialSplineMeshesQuantity = testGenerator->splineMeshesQuantity();
		bool initialSplinePointHasSplineMesh = initialSplineMeshesQuantity == 2;//splines always have start and end points at the beginning...
		UE_LOG(LogTemp, Log, TEXT("Initial spline meshes quantity in generator: %d."), initialSplineMeshesQuantity);
		UE_LOG(LogTemp, Log, TEXT("Initial spline point has spline mesh: %s."), *FString(initialSplinePointHasSplineMesh ? "true" : "false"));
		FVector arbitraryLocation = testGenerator->GetActorLocation() + FVector(1);
		testGenerator->addSplinePoint(arbitraryLocation);
		bool addedSplineIncreasesSplineMeshesQuantity = testGenerator->splineMeshesQuantity() == initialSplineMeshesQuantity + 1;
		UE_LOG(LogTemp, Log, TEXT("Spline meshes quantity after adding a spline point: %d."), testGenerator->splineMeshesQuantity());
		UE_LOG(LogTemp, Log, TEXT("Added spline point increases spline meshes quantity by one: %s."), *FString(addedSplineIncreasesSplineMeshesQuantity ? "true" : "false"));

		++tickCounter;
		if (tickCounter > tickLimit)
		{
			test->TestTrue(TEXT("When adding spline points, a spline mesh is added to the track generator."), initialSplinePointHasSplineMesh && addedSplineIncreasesSplineMeshesQuantity);
			return true;
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplinePointsShouldBeAssociatedWithSplineMeshesTest, "ProjectR.Unit.TrackGeneratorTest.SplinePointsShouldBeAssociatedWithSplineMeshes", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackGeneratorSplinePointsShouldBeAssociatedWithSplineMeshesTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnTrackGeneratorInEditorWorldCommand);

	int tickCounter = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplineMeshesCreatedCommand(tickCounter, tickLimit, this));

	//ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);clean it instead

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS