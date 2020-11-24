// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "MainMenuTest.h"
#include "Commands/MainMenuTestCommands.h"

#include "UI/MainMenu.h"

bool FUMainMenuIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UMainMenu* testFinalPhase = NewObject<UMainMenu>();

	TestNotNull(TEXT("The main menu phase shouldn't be null after instantiating it."), testFinalPhase);

	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS
