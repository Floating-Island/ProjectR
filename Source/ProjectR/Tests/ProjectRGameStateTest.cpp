// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "ProjectRGameStateTest.h"
#include "Commands/ProjectRGameStateTestCommands.h"
#include "GameState/ProjectRGameState.h"
#include "Tests/AutomationEditorCommon.h"





bool FAProjectRGameStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AProjectRGameState* testGameState = NewObject<AProjectRGameState>();
	TestNotNull(TEXT("The game state shouldn't be null after instantiating it."), testGameState);

	return true;
}


//bool FAProjectRGameStateLoadPauseMenuAddsItToViewportTest::RunTest(const FString& Parameters)
//{
//	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-GameState");
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
//	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FCheckGameStateBringsPauseMenu(this));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
//	return true;
//}





#endif //WITH_DEV_AUTOMATION_TESTS