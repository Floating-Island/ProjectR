// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "SteerStateManagerTest.h"
#include "Jet/SteerStates/SteerStateManager.h"
#include "Jet/SteerStates/CenterSteerState.h"
#include "Jet/SteerStates/LeftSteerState.h"
#include "Jet/SteerStates/RightSteerState.h"

#include "Tests/AutomationEditorCommon.h"
#include "../../Commands/CommonPIECommands.h"
#include "SteerStateManagerTestCommands.h"
#include "../../Commands/NetworkCommands.h"
#include "../../Mocks/SteerStateManagerMOCK.h"


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
	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/VoidWorld"));
	establishTestMessageTo(FString(FString("The default state should be CenterSteerState")));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* steerStateManagerClass = ASteerStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(steerStateManagerClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerCurrentState(UCenterSteerState::StaticClass(), this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FASteerStateManagerSteerLeftChangesStateToLeftSteerTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/JetMOCKTestWorld"));
	UClass* expectedStateClass = ULeftSteerState::StaticClass();
	establishTestMessageTo((FString("After leftSteer, the current state should be %s."), *expectedStateClass->GetName()));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* steerStateManagerClass = ASteerStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(steerStateManagerClass, FTransform()));
	ADD_LATENT_AUTOMATION_COMMAND(FLeftSteerASteerStateManagerMOCK);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerCurrentState(expectedStateClass, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FASteerStateManagerSteerRightChangesStateToRightSteerTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/JetMOCKTestWorld"));
	UClass* expectedStateClass = URightSteerState::StaticClass();
	establishTestMessageTo((FString("After rightSteer, the current state should be %s."), *expectedStateClass->GetName()));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* steerStateManagerClass = ASteerStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(steerStateManagerClass, FTransform()));
	ADD_LATENT_AUTOMATION_COMMAND(FRightSteerASteerStateManagerMOCK);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerCurrentState(expectedStateClass, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FASteerStateManagerCenterChangesStateToCenterSteerTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/JetMOCKTestWorld"));
	UClass* expectedStateClass = UCenterSteerState::StaticClass();
	establishTestMessageTo((FString("After center, the current state should be %s."), *expectedStateClass->GetName()));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* steerStateManagerClass = ASteerStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(steerStateManagerClass, FTransform()));
	ADD_LATENT_AUTOMATION_COMMAND(FCenterASteerStateManagerMOCK);
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerCurrentState(expectedStateClass, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;	
}


bool FASteerStateManagerSteerLeftKeepsStateIfAlreadyLeftSteerStateTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/JetMOCKTestWorld"));
	establishTestMessageTo(FString("steerLeft should keep the current state if it's a LeftSteerState."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* steerStateManagerClass = ASteerStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(steerStateManagerClass, FTransform()));

	USteerState* previousState = nullptr;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerCurrentStateAgainstPreviousOnSteerLeft(previousState, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;	
}


bool FASteerStateManagerSteerRightKeepsStateIfAlreadyRightSteerStateTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/JetMOCKTestWorld"));
	establishTestMessageTo(FString(FString("steerRight should keep the current state if it's a RightSteerState.")));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* steerStateManagerClass = ASteerStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(steerStateManagerClass, FTransform()));

	USteerState* previousState = nullptr;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerCurrentStateAgainstPreviousOnSteerRight(previousState, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;	
}


bool FASteerStateManagerCenterKeepsStateIfAlreadyCenterSteerStateTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/JetMOCKTestWorld"));
	establishTestMessageTo(FString("center should keep the current state if it's a CenterSteerState."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* steerStateManagerClass = ASteerStateManagerMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(steerStateManagerClass, FTransform()));

	USteerState* previousState = nullptr;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerCurrentStateAgainstPreviousOnCenter(previousState, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;	
}


//bool FASteerStateManagerReplicatesTest::RunTest(const FString& Parameters)
//{
//	ASteerStateManager* testManager = NewObject<ASteerStateManager>();
//
//	TestTrue(TEXT("Should replicate to the network."), testManager->GetIsReplicated());
//
//	return true;	
//}
//
//
//bool FASteerStateManagerIsAlwaysRelevantToNetworkTest::RunTest(const FString& Parameters)
//{
//	ASteerStateManager* testManager = NewObject<ASteerStateManager>();
//
//	TestTrue(TEXT("Should be always relevant to the network."), testManager->bAlwaysRelevant);
//
//	return true;	
//}
//
//
//bool FASteerStateManagerReplicatesStateWhenCallingSteerLeftTest::RunTest(const FString& Parameters)
//{
//	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/VoidWorld"));
//	UClass* expectedStateClass = ULeftSteerState::StaticClass();
//	establishTestMessageTo((FString("The current state of server and client should be %s."), *expectedStateClass->GetName()));
//	establishTickLimitTo(10);
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
//	int32 numberOfPlayers = 2;
//	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;
//
//	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));
//
//	
//	
//
//	UClass* steerStateManagerClass = ASteerStateManagerMOCK::StaticClass();
//	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnActorOfClass(steerStateManagerClass, FTransform(), numberOfPlayers));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FClientSteerLeftSteerStateManager(numberOfPlayers));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerServerAndClientExpectedState(expectedStateClass, numberOfPlayers, this));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
//	return true;
//}
//
//
//bool FASteerStateManagerReplicatesStateWhenCallingSteerRightTest::RunTest(const FString& Parameters)
//{
//	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/VoidWorld"));
//	UClass* expectedStateClass = URightSteerState::StaticClass();
//	establishTestMessageTo((FString("The current state of server and client should be %s."), *expectedStateClass->GetName()));
//	establishTickLimitTo(10);
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
//	int32 numberOfPlayers = 2;
//	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;
//
//	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));
//
//	
//	
//
//	UClass* steerStateManagerClass = ASteerStateManagerMOCK::StaticClass();
//	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnActorOfClass(steerStateManagerClass, FTransform(), numberOfPlayers));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FClientSteerRightSteerStateManager(numberOfPlayers));
//	
//	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerServerAndClientExpectedState(expectedStateClass, numberOfPlayers, this));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
//	return true;
//}
//
//
//bool FASteerStateManagerReplicatesStateWhenCallingCenterTest::RunTest(const FString& Parameters)
//{
//	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/VoidWorld"));
//	UClass* expectedStateClass = UCenterSteerState::StaticClass();
//	establishTestMessageTo((FString("The current state of server and client should be %s."), *expectedStateClass->GetName()));
//	establishTickLimitTo(10);
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
//	int32 numberOfPlayers = 2;
//	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;
//
//	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));
//
//	
//	
//
//	UClass* steerStateManagerClass = ASteerStateManagerMOCK::StaticClass();
//	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnActorOfClass(steerStateManagerClass, FTransform(), numberOfPlayers));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FClientCenterSteerStateManager(numberOfPlayers));
//	
//	ADD_LATENT_AUTOMATION_COMMAND(FCheckSteerStateManagerServerAndClientExpectedState(expectedStateClass, numberOfPlayers, this));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
//	return true;
//}








#endif //WITH_DEV_AUTOMATION_TESTS