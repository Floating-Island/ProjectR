// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "SessionHolderButtonTest.h"
#include "UI/SessionHolderButton.h"
#include "OnlineSessionSettings.h"


bool FUSessionHolderButtonIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	USessionHolderButton* testButton = NewObject<USessionHolderButton>();

	TestNotNull(TEXT("The session holder button shouldn't be null after instantiating it."), testButton);
	
	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS