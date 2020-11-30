// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "SoloRaceMenuTest.h"
#include "Commands/SoloRaceMenuTestCommands.h"
#include "Tests/AutomationEditorCommon.h"

#include "UI/SoloRaceMenu.h"

bool FUSoloRaceMenuIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	USoloRaceMenu* testSoloMenu = NewObject<USoloRaceMenu>();
	TestNotNull(TEXT("The solo race menu shouldn't be null after instantiating it."), testSoloMenu);

	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS