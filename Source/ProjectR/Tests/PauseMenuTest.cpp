// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "PauseMenuTest.h"
#include "Commands/PauseMenuTestCommands.h"
#include "UI/PauseMenu.h"
#include "Tests/AutomationEditorCommon.h"





bool FUPauseMenuIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UPauseMenu* testMenu = NewObject<UPauseMenu>();
	TestNotNull(TEXT("The pause menu shouldn't be null after instantiating it."), testMenu);

	return true;
}


bool FUPauseMenuClickingReturnButtonChangesToMainMenuMapTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo("/Game/Tests/TestMaps/VoidWorld-PlayerController");
	establishTestMessageTo(FString("The pause menu should change to the main menu map when clicking the return button."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
	
	
	

	ADD_LATENT_AUTOMATION_COMMAND(FCheckPauseMenuClickReturnButtonChangesToMainMenuMap(nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUPauseMenuClickingResumeButtonRemovesMenuFromViewportAndResumeTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo("/Game/Tests/TestMaps/VoidWorld-PlayerControllerMOCK");
	establishTestMessageTo(FString("The pause menu should be removed from viewport and resume the game when clicking on the resume button."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
	
	
	
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckPauseMenuClickResumeButtonRemovesMenuAndResumes(nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}





#endif //WITH_DEV_AUTOMATION_TESTS