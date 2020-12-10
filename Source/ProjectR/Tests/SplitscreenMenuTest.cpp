// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "SplitscreenMenuTest.h"
#include "Commands/SplitscreenMenuTestCommands.h"
#include "UI/SplitscreenMenu.h"



bool FUSplitscreenMenuIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	USplitscreenMenu* testMenu = NewObject<USplitscreenMenu>();
	TestNotNull(TEXT("The splitscreen menu shouldn't be null after instantiating it."), testMenu);

	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS