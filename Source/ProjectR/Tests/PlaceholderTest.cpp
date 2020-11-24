// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "PlaceholderTest.h"


bool FOneIsOneTest::RunTest(const FString& Parameters)
{
	//One should be one.
	TestEqual(TEXT("one is one"), 1, 1);

	return true;
}


bool FSTwoIsTwoTest::RunTest(const FString& Parameters)
{
	//two should be two.
	TestEqual(TEXT("two is two"), 2, 2);

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS