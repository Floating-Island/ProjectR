// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"


#if WITH_DEV_AUTOMATION_TESTS
/**
 * This class is intended to be used in tests where many PIE instances need to be run at the same time.
 */
class MultiplePIETestBase : public FAutomationTestBase
{
public:
	UWorld* sessionHostWorld;
	UWorld* sessionSubscriberWorld;

	MultiplePIETestBase(const FString& InName, const bool bInComplexTask)
		: FAutomationTestBase(InName, bInComplexTask)
	{
		sessionHostWorld = nullptr;
		sessionSubscriberWorld = nullptr;
	}
};


#endif