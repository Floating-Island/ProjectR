// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "AnnouncerUITest.h"
#include "UI/AnnouncerUI.h"


bool FAAnnouncerUIIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UAnnouncerUI* testAnnouncer = NewObject<UAnnouncerUI>();

	TestNotNull(TEXT("Shouldn't be null when instantiated."), testAnnouncer);

	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS