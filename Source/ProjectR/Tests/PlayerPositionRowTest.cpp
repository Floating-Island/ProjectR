// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "PlayerPositionRowTest.h"
#include "UI/PlayerPositionRow.h"
#include "Tests/AutomationEditorCommon.h"
#include "Commands/CommonPIECommands.h"
#include "Commands/PlayerPositionRowTestCommands.h"




bool FUPlayerPositionRowIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UPlayerPositionRow* testRow = NewObject<UPlayerPositionRow>();

	TestNotNull(FString("Shouldn't be null when instantiated"), testRow);

	return true;
}


bool FUPlayerPositionRowUpdatePlayerInfoWithUpdatesInfoTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-PlayerPRowContainer"));
	establishTestMessageTo(FString("The player position row should update its info when calling updateInfoWith."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnGameModeDefaultPawn);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckPlayerPositionRowUpdatesWithGivenInfo(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS