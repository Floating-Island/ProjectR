// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "LobbyGameStateTest.h"
#include "GameState/LobbyGameState.h"


bool FALobbyGameStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ALobbyGameState* testState = NewObject<ALobbyGameState>();

	TestNotNull(FString("Isn't null when instantiated"), testState);

	return true;
}





#endif //WITH_DEV_AUTOMATION_TESTS