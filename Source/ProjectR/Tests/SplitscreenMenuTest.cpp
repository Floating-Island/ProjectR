// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "SplitscreenMenuTest.h"
#include "Commands/SplitscreenMenuTestCommands.h"
#include "UI/SplitscreenMenu.h"



bool FUSplitscreenMenuIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	USplitscreenMenu* testMenu = NewObject<USplitscreenMenu>();
	TestNotNull(TEXT("The splitscreen menu shouldn't be null after instantiating it."), testMenu);

	return true;
}


bool FUSplitscreenMenuClickingGoBackButtonRemovesFromViewportTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplitscreenMenuClickGoBackRemovesFromViewportCommand(tickCount, tickLimit, nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUSplitscreenMenuClickingGoBackButtonBringsMainMenuTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSplitscreenMenuClickGoBackBringsMainMenuCommand(tickCount, tickLimit, nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS