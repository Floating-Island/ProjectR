// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS



/**
 * Simple test class able to set a test message (useful for TestTrue, TestFalse, etc. statements).
 * is able to set the test to failure if it reaches an established tick limit.
 */
class FSimplePIETestBase : public FAutomationTestBase
{
	FString initialMapDirectory;
	FString initialWorld;
	FString testMessage;
	int tickCount;
	int tickLimit;
	float timeLimit;
	FTimerHandle failureTimer;

	void appendTestFailureWhen(bool aTickCountExceedsLimit);
	void pauseCurrentPIEWorldsWhen(bool aTickCountExceedsLimit);

public:
	FSimplePIETestBase(const FString& InName, const bool bInComplexTask)
		: FAutomationTestBase(InName, bInComplexTask)
	{
		initialMapDirectory = FString();
		initialWorld = FString();
		testMessage = FString();
		tickCount = 0;
		tickLimit = 0;
		timeLimit = 0;
	}

	/**
	 * method that only sets the test message if it's empty.
	 */
	void establishInitialMapDirectoryTo(FString aWorldName);

	/**
	* method that only sets the test message if it's empty.
	*/
	void establishTestMessageTo(FString aMessage);

	/**
	 * method that only sets the tick limit on the first time it's called.
	 * It also calls resetTickCount whenever it's called.
	 */
	void establishTickLimitTo(int aDesiredQuantity);
	void increaseTickCount();
	bool tickCountExceedsLimit();

	/**
	 * checks if the tick count reaches the tick limit.
	 * If true, appends a failure message to the test.
	 * returns whether the tick count exceeds the tick limit.
	 * Should be located at the bottom of the latent command where you want to start ticking to end.
	 * inside the latent command, it should be called like: return test->manageTickCountToLimit();...
	 */
	bool manageTickCountTowardsLimit();

	/**
	 * returns the test message.
	 */
	FString conditionMessage();

	/**
	* returns the test initial map directory.
	*/
	FString retrieveInitialMapDirectory();

	/**
	* returns the test initial world name.
	*/
	FString initialWorldName();


	/**
	 * Should be called at the beginning of RunTest so if an instance of the test is already loaded, the tick count doesn't carry over to the new run.
	 */
	void resetTickCount();
};





#endif //WITH_DEV_AUTOMATION_TESTS