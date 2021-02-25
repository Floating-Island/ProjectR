// Fill out your copyright notice in the Description page of Project Settings.


#include "Commands/CommonPIECommands.h"
#if WITH_DEV_AUTOMATION_TESTS

#include "ProjectRPlayerControllerTest.h"
#include "Commands/PrRPlayerControllerTestCommands.h"
#include "PlayerController/ProjectRPlayerController.h"
#include "Tests/AutomationEditorCommon.h"





bool FAProjectRPlayerControllerIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AProjectRPlayerController* testPlayerController = NewObject<AProjectRPlayerController>();
	TestNotNull(TEXT("The player controller shouldn't be null after instantiating it."), testPlayerController);

	return true;
}


bool FAProjectRPlayerControllerLoadPauseMenuAddsItToViewportTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-PlayerController");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckPlayerControllerBringsPauseMenu(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAProjectRPlayerControllerLoadPauseMenuCreatesOnlyOneInstanceTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-PlayerController");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckPlayerControllerCreatesUniquePauseMenuInstance(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAProjectRPlayerControllerLoadPauseMenuShowsMouseCursorTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-PlayerController");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckPlayerControllerShowsMouseCursor(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAProjectRPlayerControllerEscKeyLoadsPauseMenuTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-PlayerControllerMOCK");
	establishTestMessageTo(FString("Esc key should make the controller load the pause menu."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckPlayerControllerPressEscBringsPauseMenu(nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAProjectRPlayerControllerEscKeyRemovesPauseMenuIfInViewportTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-PlayerControllerMOCK");
	establishTestMessageTo(FString("Esc key makes the controller remove the pause menu present in viewport and hide the mouse cursor."));
	establishTickLimitTo(3);
	
	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckPlayerControllerPressEscRemovesPauseMenuInViewport(nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAProjectRPlayerControllerLoadPauseMenuPausesTheGameTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-PlayerControllerMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckPlayerControllerLoadPauseMenuPausesTheGame(nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAProjectRPlayerControllerLoadPauseMenuUnPausesTheGameIfInViewportTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-PlayerControllerMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckPlayerControllerLoadPauseMenuUnPausesTheGameIfInViewport(nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAProjectRPlayerControllerFullyTicksWhenGamePausedTest::RunTest(const FString& Parameters)
{
	AProjectRPlayerController* testController = NewObject<AProjectRPlayerController>();

	TestTrue(TEXT("The controller should be set to fully tick when game is paused"), testController->ShouldPerformFullTickWhenPaused());
	return true;
}


bool FAProjectRPlayerControllerLoadsthePlayerStateUIWhenSpawnedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-ControllerRacePlayerState"));
	establishTestMessageTo(FString("The ProjectRController should load the stored PlayerState UI when spawned."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckPRPlayerControllerLoadsPlayerStateUI(nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}









#endif //WITH_DEV_AUTOMATION_TESTS