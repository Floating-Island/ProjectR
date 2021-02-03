// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "MotorStateManagerTest.h"
#include "Jet/MotorStates/MotorStateManager.h"
#include "Mocks/MotorStateManagerMOCK.h"
#include "Jet/MotorStates/AcceleratingMotorState.h"
#include "Jet/MotorStates/NeutralMotorState.h"
#include "Jet/MotorStates/ReversingMotorState.h"
#include "Jet/MotorStates/MixedMotorState.h"

#include "Tests/AutomationEditorCommon.h"
#include "Commands/CommonPIECommands.h"
#include "Commands/MotorStateManagerTestCommands.h"
#include "Commands/NetworkCommands.h"


bool FAMotorStateManagerIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AMotorStateManager* testManager = NewObject<AMotorStateManager>();

	TestNotNull(TEXT("MotorStateManager shouldn't be null when instantiated"), testManager);
	return true;
}


bool FAMotorStateManagerDefaultStateIsNeutralTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* motorStateManagerClass = AMotorStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(motorStateManagerClass, FTransform()));
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerDefaultState(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAMotorStateManagerAccelerateChangesStateToAcceleratingTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* motorStateManagerClass = AMotorStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(motorStateManagerClass, FTransform()));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAMotorStateManagerAndAccelerateIt);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerStateChangesToAccelerating(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAMotorStateManagerBrakeChangesStateToReversingTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* motorStateManagerClass = AMotorStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(motorStateManagerClass, FTransform()));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAMotorStateManagerAndBrakeIt);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerStateChangesToReversing(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAMotorStateManagerNeutralizeChangesStateToNeutralTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* motorStateManagerClass = AMotorStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(motorStateManagerClass, FTransform()));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAMotorStateManagerAndNeutralizeIt);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerStateChangesToNeutral(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAMotorStateManagerAccelerateKeepsStateIfAlreadyAcceleratingTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* motorStateManagerClass = AMotorStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(motorStateManagerClass, FTransform()));
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerAccelerateKeepsStateIfAccelerating(tickCount, tickLimit, nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAMotorStateManagerBrakeKeepsStateIfAlreadyReversingingTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* motorStateManagerClass = AMotorStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(motorStateManagerClass, FTransform()));
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerBrakeKeepsStateIfReversing(tickCount, tickLimit, nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAMotorStateManagerNeutralizeKeepsStateIfAlreadyNeutralTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* motorStateManagerClass = AMotorStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(motorStateManagerClass, FTransform()));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAMotorStateManagerAndAccelerateIt);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerNeutralizeKeepsStateIfNeutral(tickCount, tickLimit, nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


//bool FAMotorStateManagerNeutralizeAccelerateAndBrakeOnlyLeaveOneStateInMemoryTest::RunTest(const FString& Parameters)//relying on the garbage collector to destroy the replaced objects
//{
//	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
//	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FSpawnAMotorStateManagerBrakeAccelerateAndNeutralizeIt);
//	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerLeavesOneStateInWorld(this));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
//	return true;
//}


bool FAMotorStateManagerReplicatesTest::RunTest(const FString& Parameters)
{
	AMotorStateManager* testManager = NewObject<AMotorStateManager>();

	TestTrue(TEXT("Should be able to replicate"), testManager->GetIsReplicated());

	return true;
}


bool FAMotorStateManagerAlwaysRelevantTest::RunTest(const FString& Parameters)
{
	AMotorStateManager* testManager = NewObject<AMotorStateManager>();

	TestTrue(TEXT("Should be always relevant for network"), testManager->bAlwaysRelevant);

	return true;
}


bool FAMotorStateManagerReplicatesStateWhenCallingAccelerateTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	UClass* motorStateManagerClass = AMotorStateManager::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnActorOfClass(motorStateManagerClass, FTransform(), numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientAccelerateMotorStateManager(numberOfPlayers));

	int tickCount = 0;
	int tickLimit = 10;
	UClass* expectedStateClass = UAcceleratingMotorState::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerServerAndClientExpectedState(expectedStateClass , tickCount, tickLimit, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAMotorStateManagerReplicatesStateWhenCallingBrakeTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	UClass* motorStateManagerClass = AMotorStateManager::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnActorOfClass(motorStateManagerClass, FTransform(), numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientBrakeMotorStateManager(numberOfPlayers));

	int tickCount = 0;
	int tickLimit = 10;
	UClass* expectedStateClass = UReversingMotorState::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerServerAndClientExpectedState(expectedStateClass , tickCount, tickLimit, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAMotorStateManagerReplicatesStateWhenCallingNeutralizeTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	UClass* motorStateManagerClass = AMotorStateManager::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnActorOfClass(motorStateManagerClass, FTransform(), numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientNeutralizeMotorStateManager(numberOfPlayers));

	int tickCount = 0;
	int tickLimit = 10;
	UClass* expectedStateClass = UNeutralMotorState::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerServerAndClientExpectedState(expectedStateClass , tickCount, tickLimit, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAMotorStateManagerMixChangesStateToMixedTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* motorStateManagerClass = AMotorStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(motorStateManagerClass, FTransform()));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAMotorStateManagerAndMixIt);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerStateChangesToMixed(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAMotorStateManagerMixKeepsStateIfAlreadyMixedTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* motorStateManagerClass = AMotorStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(motorStateManagerClass, FTransform()));
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerMixKeepsStateIfMixed(tickCount, tickLimit, nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAMotorStateManagerReplicatesStateWhenCallingMixTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	UClass* motorStateManagerClass = AMotorStateManager::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnActorOfClass(motorStateManagerClass, FTransform(), numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientMixMotorStateManager(numberOfPlayers));

	int tickCount = 0;
	int tickLimit = 10;
	UClass* expectedStateClass = UMixedMotorState::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerServerAndClientExpectedState(expectedStateClass , tickCount, tickLimit, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAMotorStateManagerDoesntTickTest::RunTest(const FString& Parameters)
{
	AMotorStateManager* testManager = NewObject<AMotorStateManager>();

	TestFalse(TEXT("Shouldn't tick."), testManager->CanEverTick());

	return true;
}










#endif //WITH_DEV_AUTOMATION_TESTS