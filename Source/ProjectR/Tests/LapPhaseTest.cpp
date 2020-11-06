// Fill out your copyright notice in the Description page of Project Settings.


#include "LapPhaseTest.h"

#include "LapPhases/LapPhase.h"
#include "Mocks/LapPhaseMOCK.h"

#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Editor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"




#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseIsntNullWhenInstantiatedTest, "ProjectR.LapPhases Tests.Unit.000: Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapPhaseIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ALapPhase* testLapPhase = NewObject<ALapPhase>();

	TestNotNull(TEXT("The LapPhase shouldn't be null after instantiating it."), testLapPhase);

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseHasAStaticMeshComponentTest, "ProjectR.LapPhases Tests.Unit.001: Has a static mesh component", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapPhaseHasAStaticMeshComponentTest::RunTest(const FString& Parameters)
{
	ALapPhaseMOCK* testLapPhase = NewObject<ALapPhaseMOCK>();

	TestTrue(TEXT("The LapPhase should have a static mesh component after instantiating it."), testLapPhase->hasAStaticMeshComponent());

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseHasAStaticMeshTest, "ProjectR.LapPhases Tests.Unit.002: Has a static mesh associated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapPhaseHasAStaticMeshTest::RunTest(const FString& Parameters)
{
	ALapPhaseMOCK* testLapPhase = NewObject<ALapPhaseMOCK>();

	TestTrue(TEXT("The LapPhase should have a static mesh set after instantiating it."), testLapPhase->hasAStaticMeshAssociated());

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseHasPhaseWallAsRootTest, "ProjectR.LapPhases Tests.Unit.003: The phase wall is the root component", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapPhaseHasPhaseWallAsRootTest::RunTest(const FString& Parameters)
{
	ALapPhaseMOCK* testLapPhase = NewObject<ALapPhaseMOCK>();

	TestTrue(TEXT("The LapPhase should have its phase wall as the root component."), testLapPhase->phaseWallIsRootComponent());

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnALapPhaseMOCKInEditorWorldCommand);

bool FSpawnALapPhaseMOCKInEditorWorldCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}

	UWorld* testWorld = GEditor->GetEditorWorldContext().World();

	testWorld->SpawnActor<ALapPhaseMOCK>(ALapPhaseMOCK::StaticClass());

	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckLapPhaseCollisionEnabledCommand, FAutomationTestBase*, test);

bool FCheckLapPhaseCollisionEnabledCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ALapPhaseMOCK* testPhase = Cast<ALapPhaseMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ALapPhaseMOCK::StaticClass()));
	if (testPhase)
	{

		bool collisionIsQueryOnly = testPhase->hasCollisionEnabledToQueryOnly();
		UE_LOG(LogTemp, Log, TEXT("The phase wall has collision enabled to query only: %s."), *FString(collisionIsQueryOnly ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the phase wall should have collision enabled to query only."), collisionIsQueryOnly);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseHasCollisionEnabledToQueryOnlyTest, "ProjectR.LapPhase Tests.Unit.004: Has collision enabled to query only at spawning", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapPhaseHasCollisionEnabledToQueryOnlyTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnALapPhaseMOCKInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLapPhaseCollisionEnabledCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckLapPhaseCollisionResponseCommand, FAutomationTestBase*, test);

bool FCheckLapPhaseCollisionResponseCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ALapPhaseMOCK* testPhase = Cast<ALapPhaseMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ALapPhaseMOCK::StaticClass()));
	if (testPhase)
	{

		bool overlapsWithPawnChannel = testPhase->overlapsWithPawnChannel();
		UE_LOG(LogTemp, Log, TEXT("The lap phase overlaps with the pawn channel: %s."), *FString(overlapsWithPawnChannel ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the lap phase should overlap with the pawn channel."), overlapsWithPawnChannel);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseOverlapsWithPawnChannelTest, "ProjectR.LapPhase Tests.Unit.005: Overlaps with the pawn channel", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapPhaseOverlapsWithPawnChannelTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnALapPhaseMOCKInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLapPhaseCollisionResponseCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckLapPhaseObjectTypeCommand, FAutomationTestBase*, test);

bool FCheckLapPhaseObjectTypeCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ALapPhaseMOCK* testPhase = Cast<ALapPhaseMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ALapPhaseMOCK::StaticClass()));
	if (testPhase)
	{

		bool objectTypeIsWorldStatic = testPhase->objectTypeIsWorldStatic();
		UE_LOG(LogTemp, Log, TEXT("The lap phase object type is world static: %s."), *FString(objectTypeIsWorldStatic ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the lap phase object type should be world static."), objectTypeIsWorldStatic);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseObjectTypeIsWorldStaticTest, "ProjectR.LapPhase Tests.Unit.006: Its object type is world static", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapPhaseObjectTypeIsWorldStaticTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnALapPhaseMOCKInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLapPhaseObjectTypeCommand(this));

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckLapPhaseOverlapEventsCommand, FAutomationTestBase*, test);

bool FCheckLapPhaseOverlapEventsCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ALapPhaseMOCK* testPhase = Cast<ALapPhaseMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ALapPhaseMOCK::StaticClass()));
	if (testPhase)
	{

		bool generatesOverlapEvents = testPhase->generatesOverlapEvents();
		UE_LOG(LogTemp, Log, TEXT("The lap phase generates overlap events: %s."), *FString(generatesOverlapEvents ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the lap phase should generate overlap events."), generatesOverlapEvents);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseGeneratesOverlapEventsTest, "ProjectR.LapPhase Tests.Unit.007: Generates overlap events", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapPhaseGeneratesOverlapEventsTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnALapPhaseMOCKInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLapPhaseOverlapEventsCommand(this));

	return true;
}






IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseUpdateStateReturnsItselfTest, "ProjectR.LapPhases Tests.Unit.008: updateState returns itself", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapPhaseUpdateStateReturnsItselfTest::RunTest(const FString& Parameters)
{
	ALapPhase* testLapPhase = NewObject<ALapPhase>();

	TestTrue(TEXT("The LapPhase should return itself when calling updateState."), testLapPhase->updatePhase(testLapPhase) == testLapPhase);

	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS
