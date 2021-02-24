// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "RacePlayerUITest.h"
#include "UI/RacePlayerUI.h"


bool FARacePlayerUIIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	URacePlayerUI* testPlayerUI = NewObject<URacePlayerUI>();

	TestNotNull(TEXT("Shouldn't be null when instantiated"), testPlayerUI);
	
	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS