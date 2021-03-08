// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "RaceResultsUITest.h"

#include "UI/RaceResultsUI.h"
#include "Tests/AutomationEditorCommon.h"
#include "Commands/CommonPIECommands.h"
#include "Commands/RaceResultsUITestCommands.h"


bool FURaceResultsUIIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	URaceResultsUI* testResults = NewObject<URaceResultsUI>();

	TestNotNull(FString("Shouldn't be null when instantiated"), testResults);

	return true;
}


bool FURaceResultsUIFillsInfoBoxWithRaceGameStatePlayerStatesInfoTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-RaceResultsAndFriends"));
	establishTestMessageTo(FString("The player position row should update its info when calling updateInfoWith."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	
	
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnGameModeDefaultPawn);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckRaceResultsInfoBoxQuantitySameAsPlayerStates(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS