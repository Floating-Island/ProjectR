// Fill out your copyright notice in the Description page of Project Settings.







#if WITH_DEV_AUTOMATION_TESTS


#include "LapPhaseTest.h"
#include "LapPhaseTestCommands.h"
#include "LapPhases/LapPhase.h"
#include "../../Mocks/LapPhaseMOCK.h"
#include "../../Commands/CommonPIECommands.h"

#include "Tests/AutomationEditorCommon.h"



bool FALapPhaseIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ALapPhase* testLapPhase = NewObject<ALapPhase>();
	TestNotNull(FString("The LapPhase shouldn't be null after instantiating it."), testLapPhase);

	return true;
}


bool FALapPhaseHasAStaticMeshComponentTest::RunTest(const FString& Parameters)
{
	ALapPhaseMOCK* testLapPhase = NewObject<ALapPhaseMOCK>();
	TestTrue(FString("The LapPhase should have a static mesh component after instantiating it."), testLapPhase->hasAStaticMeshComponent());

	return true;
}


bool FALapPhaseHasAStaticMeshTest::RunTest(const FString& Parameters)
{
	ALapPhaseMOCK* testLapPhase = NewObject<ALapPhaseMOCK>();
	TestTrue(FString("The LapPhase should have a static mesh set after instantiating it."), testLapPhase->hasAStaticMeshAssociated());

	return true;
}


bool FALapPhaseHasPhaseWallAsRootTest::RunTest(const FString& Parameters)
{
	ALapPhaseMOCK* testLapPhase = NewObject<ALapPhaseMOCK>();
	TestTrue(FString("The LapPhase should have its phase wall as the root component."), testLapPhase->phaseWallIsRootComponent());

	return true;
}


bool FALapPhaseHasCollisionEnabledToQueryOnlyTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* lapPhaseClass = ALapPhaseMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(lapPhaseClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLapPhaseCollisionEnabled(this));

	return true;
}


bool FALapPhaseOverlapsWithPawnChannelTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* lapPhaseClass = ALapPhaseMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(lapPhaseClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLapPhaseCollisionResponse(this));

	return true;
}


bool FALapPhaseObjectTypeIsWorldStaticTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* lapPhaseClass = ALapPhaseMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(lapPhaseClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLapPhaseObjectType(this));

	return true;
}


bool FALapPhaseGeneratesOverlapEventsTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	UClass* lapPhaseClass = ALapPhaseMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInEditorAnActorOfClass(lapPhaseClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLapPhaseOverlapEvents(this));

	return true;
}


bool FALapPhaseUpdateStateReturnsItselfTest::RunTest(const FString& Parameters)
{
	ALapPhase* testLapPhase = NewObject<ALapPhase>();
	TestTrue(FString("The LapPhase should return itself when calling updateState."), testLapPhase->updatePhase(testLapPhase) == testLapPhase);

	return true;
}


bool FALapPhaseIsHiddenInGameTest::RunTest(const FString& Parameters)
{
	ALapPhaseMOCK* testLapPhase = NewObject<ALapPhaseMOCK>();
	TestTrue(FString("The LapPhase should be hidden in game."), testLapPhase->IsHiddenInGame());

	return true;
}


bool FALapPhaseDefaultAllowedDistanceIsMaximumPossibleTest::RunTest(const FString& Parameters)
{
	ALapPhase* testLapPhase = NewObject<ALapPhase>();
	TestTrue(FString("The LapPhase allowed distance should be the maximum possible by default."), 
		FMath::IsNearlyEqual(testLapPhase->maximumAllowedDistance(), std::numeric_limits<float>::max()));

	return true;	
}

#endif //WITH_DEV_AUTOMATION_TESTS
