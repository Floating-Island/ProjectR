// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "PauseMenuTest.h"
#include "Commands/PauseMenuTestCommands.h"
#include "UI/PauseMenu.h"





bool FUPauseMenuIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UPauseMenu* testMenu = NewObject<UPauseMenu>();
	TestNotNull(TEXT("The pause menu shouldn't be null after instantiating it."), testMenu);

	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS