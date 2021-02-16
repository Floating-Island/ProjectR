// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "SessionSelectorScrollBoxTest.h"
#include "UI/SessionSelectorScrollBox.h"




bool FUSessionSelectorScrollBoxIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	USessionSelectorScrollBox* testButton = NewObject<USessionSelectorScrollBox>();

	TestNotNull(TEXT("The session holder button shouldn't be null after instantiating it."), testButton);
	
	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS