// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "SessionManagerTest.h"
#include "Session/SessionManager.h"
#include "Mocks/SessionManagerMOCK.h"
#include "Tests/AutomationEditorCommon.h"
#include "Commands/CommonPIECommands.h"
#include "Commands/SessionManagerTestCommands.h"
#include "Utilities/ObjectContainerActor.h"


bool FUSessionManagerIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	USessionManager* testManager = NewObject<USessionManager>();

	TestNotNull("Shouldn't be null when instantiated.", testManager);

	return true;
}


bool FUSessionManagerHasTheSessionSubsystemWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	USessionManagerMOCK* testManager = NewObject<USessionManagerMOCK>();

	TestNotNull("Session subsystem shouldn't be null when instantiated.", testManager->retrieveSessionSubsystem());

	return true;
}


bool FUSessionManagerHasTheSessionInterfaceWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	USessionManagerMOCK* testManager = NewObject<USessionManagerMOCK>();

	TestNotNull("Session interface shouldn't be null when instantiated.", testManager->retrieveSessionInterface().Get());

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

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS