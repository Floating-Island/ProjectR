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
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-PlayerController");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckPauseMenuClickReturnButtonChangesToMainMenuMap(tickCount, tickLimit, nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS