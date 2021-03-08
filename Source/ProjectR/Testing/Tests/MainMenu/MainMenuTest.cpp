// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "MainMenuTest.h"
#include "MainMenuTestCommands.h"
#include "Tests/AutomationEditorCommon.h"

#include "UI/MainMenu.h"

bool FUMainMenuIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UMainMenu* testMainMenu = NewObject<UMainMenu>();
	TestNotNull(TEXT("The main menu shouldn't be null after instantiating it."), testMainMenu);

	return true;
}


bool FUMainMenuClickingQuitButtonQuitsTheGameTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The main menu should quit the game when clicking the quit button."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	
	
	bool inPIE = false;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMainMenuClickQuits(inPIE, nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUMainMenuClickingSingleplayerButtonRemovesMenuFromViewportTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The main menu should be removed from viewport when clicking the singleplayer button."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMainMenuClickSingleplayerRemovesMenuFromViewport(nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUMainMenuClickingSingleplayerButtonBringsSingleplayerMenuTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The main menu should change to the singleplayer menu when clicking the singleplayer button."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMainMenuClickSingleplayerBringsSingleplayerMenu(nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUMainMenuClickingLocalMultiplayerButtonRemovesMenuFromViewportTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The main menu should be removed from viewport when clicking the local multiplayer button."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMainMenuClickLocalMultiplayerRemovesMenuFromViewport(nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUMainMenuClickingLocalMultiplayerButtonBringsLocalMultiplayerMenuTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The main menu should change to the local multiplayer menu when clicking the local multiplayer button."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSoloMainMenuClickLocalMultiplayerBringsLocalMultiplayerMenu(nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUMainMenuClickingLanMultiplayerButtonRemovesMenuFromViewportTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The main menu should be removed from viewport when clicking the lan multiplayer button."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FCheckMainMenuClickLanMultiplayerRemovesMenuFromViewport(nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUMainMenuClickingLanMultiplayerButtonBringsLanMultiplayerMenuTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The main menu should load the lan multiplayer menu when clicking the lan multiplayer button."));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMainMenuClickLanMultiplayerBringsLanMultiplayerMenu(nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS
