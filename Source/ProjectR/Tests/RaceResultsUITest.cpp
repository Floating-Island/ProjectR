// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "RaceResultsUITest.h"

#include "UI/RaceResultsUI.h"


bool FURaceResultsUIIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	URaceResultsUI* testResults = NewObject<URaceResultsUI>();


	TestNotNull(FString("Shouldn't be null when instantiated"), testResults);

	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS