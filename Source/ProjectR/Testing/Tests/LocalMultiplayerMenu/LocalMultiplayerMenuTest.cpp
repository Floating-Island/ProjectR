// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "LocalMultiplayerMenuTest.h"
#include "LocalMultiplayerMenuTestCommands.h"
#include "UI/LocalMultiplayerMenu.h"
#include "Tests/AutomationEditorCommon.h"


bool FULocalMultiplayerMenuIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ULocalMultiplayerMenu* testMenu = NewObject<ULocalMultiplayerMenu>();
	TestNotNull(TEXT("The splitscreen menu shouldn't be null after instantiating it."), testMenu);

	return true;
}


bool FULocalMultiplayerMenuClickingGoBackButtonRemovesFromViewportTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The local multiplayer menu should be removed from viewport when clicking the go back button."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLocalMultiplayerMenuClickGoBackRemovesFromViewport(nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FULocalMultiplayerMenuClickingGoBackButtonBringsMainMenuTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The local multiplayer menu should change to the main menu when clicking the go back button."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLocalMultiplayerMenuClickGoBackBringsMainMenu(nullptr,this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FULocalMultiplayerMenuClickingPlayButtonSetsPlayerQuantityTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The local multiplayer menu should set the expected players set in the combo box."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	int numberOfPlayers = 0;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckLocalMultiplayerMenuClickPlaySetsPlayers(nullptr, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FULocalMultiplayerMenuClickingPlayButtonChangesMapTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The local multiplayer menu should change the current map when clicking the play button."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FChecklocalMultiplayerMenuClickPlayButtonChangesMap(nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS