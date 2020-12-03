// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "ProjectRGameStateTest.h"
#include "Commands/ProjectRGameStateTestCommands.h"
#include "GameState/ProjectRGameState.h"





bool FAProjectRGameStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AProjectRGameState* testGameState = NewObject<AProjectRGameState>();
	TestNotNull(TEXT("The game state shouldn't be null after instantiating it."), testGameState);

	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS