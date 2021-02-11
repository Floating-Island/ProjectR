// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "SessionManagerTest.h"
#include "Session/SessionManager.h"
#include "Mocks/SessionManagerMOCK.h"
#include "Tests/AutomationEditorCommon.h"
#include "Commands/CommonPIECommands.h"
#include "Commands/SessionManagerTestCommands.h"
#include "Utilities/ObjectContainerActor.h"
#include "OnlineSessionSettings.h"


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


bool FUSessionManagerSessionSearchResultsReturnsIDsFromSearchResultsTest::RunTest(const FString& Parameters)
{
	USessionManagerMOCK* testManager = NewObject<USessionManagerMOCK>();

	TSharedPtr<FOnlineSessionSearch> dummySearchResults = MakeShared<FOnlineSessionSearch>();


	TArray<FOnlineSessionSearchResult> falseResults = TArray<FOnlineSessionSearchResult>();
	FOnlineSessionSearchResult falseSessionResult = FOnlineSessionSearchResult();

	FOnlineSession falseSession = FOnlineSession();
	falseSessionResult.Session = falseSession;
	falseResults.Add(falseSessionResult);

	bool startsWithoutSearchResults = testManager->sessionSearchResults().Num() == 0;
	
	testManager->setArbitrarySessionSearchResults(falseResults);

	bool returnsSearchResults = testManager->sessionSearchResults().Num() > 0;

	TestTrue(TEXT("sessionSearchResults returns the search Results session ID's"), startsWithoutSearchResults && returnsSearchResults);

	return true;
}







#endif //WITH_DEV_AUTOMATION_TESTS