// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "SessionManagerTest.h"
#include "Session/SessionManager.h"
#include "Mocks/SessionManagerMOCK.h"
#include "Tests/AutomationEditorCommon.h"
#include "Commands/CommonPIECommands.h"
#include "Commands/SessionManagerTestCommands.h"
#include "Utilities/ObjectContainerActor.h"
#include "Commands/NetworkCommands.h"


bool FUSessionManagerIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	USessionManager* testManager = NewObject<USessionManager>();

	TestNotNull("Shouldn't be null when instantiated.", testManager);

	return true;
}


bool FUSessionManagerCreateLANSessionStartsTheCreationOfSessionTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* containerClass = AObjectContainerActor::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(containerClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FUSessionManagerCreateAndCheckSessionCreation(this));
	//to the command above add destroy session after checking. If not, further tests that want to create a session will fail...
	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUSessionManagerCreateLANSessionTravelsToLobbyWhenStartedTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* containerClass = AObjectContainerActor::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(containerClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FUSessionManagerCreateSession);

	int tickCount = 0;
	int tickLimit = 10;
	ADD_LATENT_AUTOMATION_COMMAND(FUSessionManagerCheckTravelToLobby(tickCount, tickLimit, this));
	//to the command above add destroy session after checking. If not, further tests that want to create a session will fail...
	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUSessionManagerDestroyCurrentSessionStartsSessionDestructionTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* containerClass = AObjectContainerActor::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(containerClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FUSessionManagerCreateSession);

	int tickCount = 0;
	int tickLimit = 10;
	ADD_LATENT_AUTOMATION_COMMAND(FUSessionManagerCheckSessionDestructionStarting(tickCount, tickLimit, this));
	//to the command above add destroy session after checking. If not, further tests that want to create a session will fail...
	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUSessionManagerSearchLANSessionsStartsTheSearchOfSessionsTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* containerClass = AObjectContainerActor::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(containerClass, FTransform()));

	int tickCount = 0;
	int tickLimit = 10;
	ADD_LATENT_AUTOMATION_COMMAND(FUSessionManagerCheckSessionSearching(tickCount, tickLimit, this));
	//to the command above add destroy session after checking. If not, further tests that want to create a session will fail...
	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUSessionManagerServerCreateSessionAppearsInClientSessionSearchTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");
	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	UClass* objectContainerClass = AObjectContainerActor::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnActorOfClass(objectContainerClass, FTransform(), numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FServerCreateLANSession(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientSpawnSessionManager(numberOfPlayers));

	int tickCount = 0;
	int tickLimit = 10;
	ADD_LATENT_AUTOMATION_COMMAND(FUSessionManagerCheckClientFindsAtLeastOneLANSession(tickCount, tickLimit, numberOfPlayers, this));
	
	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}





#endif //WITH_DEV_AUTOMATION_TESTS