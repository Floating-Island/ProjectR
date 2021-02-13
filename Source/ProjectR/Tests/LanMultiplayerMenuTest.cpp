// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "LanMultiplayerMenuTest.h"

#include "UI/LanMultiplayerMenu.h"

bool FULanMultiplayerMenuIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ULanMultiplayerMenu* testLanMultiplayerMenu = NewObject<ULanMultiplayerMenu>();
	TestNotNull(TEXT("The LAN multiplayer menu shouldn't be null after instantiating it."), testLanMultiplayerMenu);

	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS
