// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "SteerStateManagerTest.h"
#include "Jet/SteerStates/SteerStateManager.h"
#include "Jet/SteerStates/CenterSteerState.h"
#include "Jet/SteerStates/LeftSteerState.h"
#include "Jet/SteerStates/RightSteerState.h"

#include "Tests/AutomationEditorCommon.h"
#include "Commands/SteerStateManagerTestCommands.h"


bool FASteerStateManagerIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ASteerStateManager* testManager = NewObject<ASteerStateManager>();

	TestNotNull(TEXT("Shouldn't be null when instantiated."), testManager);

	return true;
}


bool FASteerStateManagerDoesntTickTest::RunTest(const FString& Parameters)
{
	ASteerStateManager* testManager = NewObject<ASteerStateManager>();

	TestFalse(TEXT("Shouldn't tick."), testManager->CanEverTick());

	return true;	
}


bool FASteerStateManagerDefaultStateIsCenterTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnASteerStateManagerMOCK);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerCurrentState(UCenterSteerState::StaticClass(), FString("The default state should be CenterSteerState"), tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FASteerStateManagerSteerLeftChangesStateToLeftSteerTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnASteerStateManagerMOCK);
	ADD_LATENT_AUTOMATION_COMMAND(FLeftSteerASteerStateManagerMOCK);
	int tickCount = 0;
	int tickLimit = 3;
	UClass* expectedStateClass = ULeftSteerState::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerCurrentState(expectedStateClass, (FString("After leftSteer, the current state should be %s."), *expectedStateClass->GetName()), tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FASteerStateManagerSteerRightChangesStateToRightSteerTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnASteerStateManagerMOCK);
	ADD_LATENT_AUTOMATION_COMMAND(FRightSteerASteerStateManagerMOCK);
	int tickCount = 0;
	int tickLimit = 3;
	UClass* expectedStateClass = URightSteerState::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerCurrentState(expectedStateClass, (FString("After rightSteer, the current state should be %s."), *expectedStateClass->GetName()), tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FASteerStateManagerCenterChangesStateToCenterSteerTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnASteerStateManagerMOCK);
	ADD_LATENT_AUTOMATION_COMMAND(FCenterASteerStateManagerMOCK);
	int tickCount = 0;
	int tickLimit = 3;
	UClass* expectedStateClass = UCenterSteerState::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerCurrentState(expectedStateClass, (FString("After center, the current state should be %s."), *expectedStateClass->GetName()), tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;	
}


bool FASteerStateManagerSteerLeftKeepsStateIfAlreadyLeftSteerStateTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnASteerStateManagerMOCK);
	ADD_LATENT_AUTOMATION_COMMAND(FLeftSteerASteerStateManagerMOCKIndefinitely);
	int tickCount = 0;
	int tickLimit = 3;
	USteerState* previousState = nullptr;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerCurrentStateAgainstPrevious(previousState, FString("leftSteer should keep the current state if it's a LeftSteerState."), tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;	
}







#endif //WITH_DEV_AUTOMATION_TESTS