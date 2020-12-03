// Fill out your copyright notice in the Description page of Project Settings.



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






#endif //WITH_DEV_AUTOMATION_TESTS