// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "StringScrollBoxTest.h"
#include "UI/StringButtonScrollBox.h"

#include "Tests/AutomationEditorCommon.h"
#include "Commands/StringScrollBoxTestCommands.h"



bool FUStringButtonScrollBoxIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UStringButtonScrollBox* testScroll = NewObject<UStringButtonScrollBox>();

	TestNotNull(TEXT("The string button scroll box shouldn't be null after instantiating it."), testScroll);
	
	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS