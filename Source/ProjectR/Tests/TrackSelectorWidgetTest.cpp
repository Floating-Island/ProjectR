// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "TrackSelectorWidgetTest.h"
#include "../Public/UI/TrackSelectorWidget.h"



bool FUTrackSelectorWidgetIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UTrackSelectorWidget* testSelector = NewObject<UTrackSelectorWidget>();

	TestNotNull(TEXT("Isn't null when instantiated."), testSelector);
	
	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS