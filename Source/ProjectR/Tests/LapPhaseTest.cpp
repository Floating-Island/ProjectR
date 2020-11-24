// Fill out your copyright notice in the Description page of Project Settings.







#if WITH_DEV_AUTOMATION_TESTS


#include "LapPhaseTest.h"
#include "Commands/LapPhaseTestCommands.h"
#include "LapPhases/LapPhase.h"
#include "Mocks/LapPhaseMOCK.h"

#include "Tests/AutomationEditorCommon.h"



bool FALapPhaseIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ALapPhase* testLapPhase = NewObject<ALapPhase>();
	TestNotNull(TEXT("The LapPhase shouldn't be null after instantiating it."), testLapPhase);

	return true;
}


bool FALapPhaseHasAStaticMeshComponentTest::RunTest(const FString& Parameters)
{
	ALapPhaseMOCK* testLapPhase = NewObject<ALapPhaseMOCK>();
	TestTrue(TEXT("The LapPhase should have a static mesh component after instantiating it."), testLapPhase->hasAStaticMeshComponent());

	return true;
}


bool FALapPhaseHasAStaticMeshTest::RunTest(const FString& Parameters)
{
	ALapPhaseMOCK* testLapPhase = NewObject<ALapPhaseMOCK>();
	TestTrue(TEXT("The LapPhase should have a static mesh set after instantiating it."), testLapPhase->hasAStaticMeshAssociated());

	return true;
}


bool FALapPhaseHasPhaseWallAsRootTest::RunTest(const FString& Parameters)
{
	ALapPhaseMOCK* testLapPhase = NewObject<ALapPhaseMOCK>();
	TestTrue(TEXT("The LapPhase should have its phase wall as the root component."), testLapPhase->phaseWallIsRootComponent());

	return true;
}


bool FALapPhaseHasCollisionEnabledToQueryOnlyTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnALapPhaseMOCKInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLapPhaseCollisionEnabledCommand(this));

	return true;
}


bool FALapPhaseOverlapsWithPawnChannelTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnALapPhaseMOCKInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLapPhaseCollisionResponseCommand(this));

	return true;
}


bool FALapPhaseObjectTypeIsWorldStaticTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnALapPhaseMOCKInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLapPhaseObjectTypeCommand(this));

	return true;
}


bool FALapPhaseGeneratesOverlapEventsTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnALapPhaseMOCKInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLapPhaseOverlapEventsCommand(this));

	return true;
}


bool FALapPhaseUpdateStateReturnsItselfTest::RunTest(const FString& Parameters)
{
	ALapPhase* testLapPhase = NewObject<ALapPhase>();
	TestTrue(TEXT("The LapPhase should return itself when calling updateState."), testLapPhase->updatePhase(testLapPhase) == testLapPhase);

	return true;
}


bool FALapPhaseIsHiddenInGameTest::RunTest(const FString& Parameters)
{
	ALapPhaseMOCK* testLapPhase = NewObject<ALapPhaseMOCK>();
	TestTrue(TEXT("The LapPhase should be hidden in game."), testLapPhase->IsHiddenInGame());

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS
