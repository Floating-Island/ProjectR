// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "SteerStateManagerTest.h"
#include "Jet/SteerStates/SteerStateManager.h"
#include "Jet/SteerStates/CenterSteerState.h"
#include "Jet/SteerStates/LeftSteerState.h"
#include "Jet/SteerStates/RightSteerState.h"

#include "Tests/AutomationEditorCommon.h"
#include "Commands/SteerStateManagerTestCommands.h"
#include "Commands/NetworkCommands.h"
#include "Mocks/SteerStateManagerMOCK.h"


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
	int tickCount = 0;
	int tickLimit = 3;
	USteerState* previousState = nullptr;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerCurrentStateAgainstPreviousOnSteerLeft(previousState, FString("steerLeft should keep the current state if it's a LeftSteerState."), tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;	
}


bool FASteerStateManagerSteerRightKeepsStateIfAlreadyRightSteerStateTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnASteerStateManagerMOCK);
	int tickCount = 0;
	int tickLimit = 3;
	USteerState* previousState = nullptr;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerCurrentStateAgainstPreviousOnSteerRight(previousState, FString("steerRight should keep the current state if it's a RightSteerState."), tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;	
}


bool FASteerStateManagerCenterKeepsStateIfAlreadyCenterSteerStateTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnASteerStateManagerMOCK);
	int tickCount = 0;
	int tickLimit = 3;
	USteerState* previousState = nullptr;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerCurrentStateAgainstPreviousOnCenter(previousState, FString("center should keep the current state if it's a CenterSteerState."), tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;	
}


bool FASteerStateManagerReplicatesTest::RunTest(const FString& Parameters)
{
	ASteerStateManager* testManager = NewObject<ASteerStateManager>();

	TestTrue(TEXT("Should replicate to the network."), testManager->GetIsReplicated());

	return true;	
}


bool FASteerStateManagerIsAlwaysRelevantToNetworkTest::RunTest(const FString& Parameters)
{
	ASteerStateManager* testManager = NewObject<ASteerStateManager>();

	TestTrue(TEXT("Should be always relevant to the network."), testManager->bAlwaysRelevant);

	return true;	
}


bool FASteerStateManagerReplicatesStateWhenCallingSteerLeftTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	UClass* steerStateManagerClass = ASteerStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnSteerStateManagerMOCK(steerStateManagerClass, numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientSteerLeftSteerStateManager(numberOfPlayers));

	int tickCount = 0;
	int tickLimit = 10;
	UClass* expectedStateClass = ULeftSteerState::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerServerAndClientExpectedState(expectedStateClass, tickCount, tickLimit, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FASteerStateManagerReplicatesStateWhenCallingSteerRightTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	UClass* steerStateManagerClass = ASteerStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnSteerStateManagerMOCK(steerStateManagerClass, numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientSteerRightSteerStateManager(numberOfPlayers));

	int tickCount = 0;
	int tickLimit = 10;
	UClass* expectedStateClass = URightSteerState::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerServerAndClientExpectedState(expectedStateClass, tickCount, tickLimit, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FASteerStateManagerReplicatesStateWhenCallingCenterTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	UClass* steerStateManagerClass = ASteerStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnSteerStateManagerMOCK(steerStateManagerClass, numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientCenterSteerStateManager(numberOfPlayers));

	int tickCount = 0;
	int tickLimit = 10;
	UClass* expectedStateClass = UCenterSteerState::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerServerAndClientExpectedState(expectedStateClass, tickCount, tickLimit, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}








#endif //WITH_DEV_AUTOMATION_TESTS