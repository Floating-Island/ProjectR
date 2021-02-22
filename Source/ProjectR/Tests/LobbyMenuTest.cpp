// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "LobbyMenuTest.h"
#include "UI/LobbyMenu.h"

bool FULobbyMenuIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ULobbyMenu* testMenu = NewObject<ULobbyMenu>();

	TestNotNull(TEXT("Shouldn't be null when instantiated."), testMenu);

	return true;
}





#endif //WITH_DEV_AUTOMATION_TESTS