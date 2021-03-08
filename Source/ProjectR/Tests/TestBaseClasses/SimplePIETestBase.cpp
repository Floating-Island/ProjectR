// Fill out your copyright notice in the Description page of Project Settings.

#include "SimplePIETestBase.h"
#include "../Utilities/PIESessionUtilities.h"

#if WITH_DEV_AUTOMATION_TESTS



void FSimplePIETestBase::appendTestFailureWhen(bool aTickCountExceedsLimit)
{
	if(aTickCountExceedsLimit)
	{
		FString limitReachedMessage = FString(TEXT("Tick limit of %d reached. "), tickLimit) + testMessage;
		TestFalse(*limitReachedMessage, aTickCountExceedsLimit);
	}
}

void FSimplePIETestBase::pauseCurrentPIEWorldWhen(bool aTickCountExceedsLimit)
{
	if(aTickCountExceedsLimit)
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
	}
}

void FSimplePIETestBase::timeLimitReached()
{
	bool timeUp = true;
	FString limitReachedMessage = FString(TEXT("Time limit of %f reached. "), timeLimit) + testMessage;
	TestFalse(*limitReachedMessage, timeUp);
}

void FSimplePIETestBase::increaseTickCount()
{
	++tickCount;
}

void FSimplePIETestBase::establishInitialMapDirectoryTo(FString aWorldName)
{
	if(initialMapDirectory.IsEmpty())
	{
		initialMapDirectory = aWorldName;
	}
}

void FSimplePIETestBase::establishTestMessageTo(FString aMessage)
{
	if(testMessage.IsEmpty())
	{
		testMessage = aMessage;
	}
}

void FSimplePIETestBase::establishTickLimitTo(int aDesiredQuantity)
{
	if(tickLimit == 0)
	{
		tickLimit = aDesiredQuantity;
	}
}

bool FSimplePIETestBase::tickCountExceedsLimit()
{
	return tickCount > tickLimit;
}

bool FSimplePIETestBase::manageTickCountTowardsLimit()
{
	bool tickCountExceedsTheLimit = tickCountExceedsLimit();

	appendTestFailureWhen(tickCountExceedsTheLimit);
	pauseCurrentPIEWorldWhen(tickCountExceedsTheLimit);
	increaseTickCount();

	return tickCountExceedsTheLimit;
}

FString FSimplePIETestBase::conditionMessage()
{
	return testMessage;
}

FString FSimplePIETestBase::retrieveInitialMapDirectory()
{
	return initialMapDirectory;
}

FString FSimplePIETestBase::initialWorldName()
{
	if(initialWorld.IsEmpty())
	{
		FString mapName = FString();
		FString discard = FString();
		initialMapDirectory.Split("/", &discard, &mapName, ESearchCase::IgnoreCase, ESearchDir::FromEnd);

		initialWorld = mapName;
	}
	return initialWorld;
}

void FSimplePIETestBase::establishTimeLimitAt(float anAmountOfSeconds)
{
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	FTimerManager& globalTimer = sessionUtilities.currentPIEWorld()->GetTimerManager();

	if(globalTimer.TimerExists(failureTimer))
	{
		return;
	}
	FTimerDelegate countdownDelegate = FTimerDelegate::CreateUObject(this, &FSimplePIETestBase::timeLimitReached);
	globalTimer.SetTimer(failureTimer, countdownDelegate, anAmountOfSeconds, false);
}


#endif //WITH_DEV_AUTOMATION_TESTS
