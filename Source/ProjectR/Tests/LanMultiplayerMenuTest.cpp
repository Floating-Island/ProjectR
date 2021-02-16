// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "LanMultiplayerMenuTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Commands/LanMultiplayerMenuTestCommands.h"

#include "UI/LanMultiplayerMenu.h"

bool FULanMultiplayerMenuIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ULanMultiplayerMenu* testLanMultiplayerMenu = NewObject<ULanMultiplayerMenu>();
	TestNotNull(TEXT("The LAN multiplayer menu shouldn't be null after instantiating it."), testLanMultiplayerMenu);

	return true;
}


bool FULanMultiplayerMenuClickingGoBackButtonRemovesFromViewportTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLanMultiplayerMenuClickGoBackRemovesFromViewport(nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS
