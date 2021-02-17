// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "StringHolderButtonTest.h"
#include "UI/StringHolderButton.h"


bool FUStringHolderButtonIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UStringHolderButton* testButton = NewObject<UStringHolderButton>();

	TestNotNull(TEXT("The string holder button shouldn't be null after instantiating it."), testButton);
	
	return true;
}


bool FUStringHolderButtonStoresStringsTest::RunTest(const FString& Parameters)
{
	UStringHolderButton* testButton = NewObject<UStringHolderButton>();

	FString testString = FString("I'm a string.");
	
	testButton->store(testString);
	
	TestTrue(TEXT("The string holder button should be able to store a FString."), testButton->storedString().Contains(testString));
	
	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS