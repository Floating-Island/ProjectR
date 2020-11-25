// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "MainMenuTest.h"
#include "Commands/MainMenuTestCommands.h"
#include "Tests/AutomationEditorCommon.h"

#include "UI/MainMenu.h"

bool FUMainMenuIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UMainMenu* testFinalPhase = NewObject<UMainMenu>();
	TestNotNull(TEXT("The main menu phase shouldn't be null after instantiating it."), testFinalPhase);

	return true;
}


bool FUMainMenuQuitQuitsTheGameTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnMainMenuAndPressQuitInPIE);
	int tickCount = 0;
	int tickLimit = 3;
	bool inPIE = false;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMainMenuQuitsCommand(inPIE, tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS
