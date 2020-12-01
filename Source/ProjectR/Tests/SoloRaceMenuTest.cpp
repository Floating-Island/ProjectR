// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "SoloRaceMenuTest.h"
#include "Commands/SoloRaceMenuTestCommands.h"
#include "Tests/AutomationEditorCommon.h"

#include "UI/SoloRaceMenu.h"

bool FUSoloRaceMenuIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	USoloRaceMenu* testSoloMenu = NewObject<USoloRaceMenu>();
	TestNotNull(TEXT("The solo race menu shouldn't be null after instantiating it."), testSoloMenu);

	return true;
}


bool FUSoloRaceMenuClickingPlayButtonChangesMapTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
	
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSoloRaceMenuClickChangesMapCommand(tickCount, tickLimit, nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUSoloRaceMenuClickingGoBackButtonRemovesFromViewportTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
	
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSoloRaceMenuClickGoBackRemovesFromViewportCommand(tickCount, tickLimit, nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS