// Fill out your copyright notice in the Description page of Project Settings.

#include "SimplePIETestBase.h"
#include "../Utilities/PIESessionUtilities.h"

#if WITH_DEV_AUTOMATION_TESTS



void FSimplePIETestBase::appendTestFailureWhen(bool aTickCountExceedsLimit)
{
	if(aTickCountExceedsLimit)
	{
		FString limitReachedMessage = FString("Tick limit of ") + FString::FromInt(tickLimit) + FString(" reached. ") + testMessage;
		TestFalse(*limitReachedMessage, aTickCountExceedsLimit);
	}
}

void FSimplePIETestBase::pauseCurrentPIEWorldsWhen(bool aTickCountExceedsLimit)
{
	if(aTickCountExceedsLimit)
	{
		for(auto context : GEditor->GetWorldContexts())
		{
			context.World()->bDebugFrameStepExecution = true;
		}
	}
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
	resetTickCount();
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
	pauseCurrentPIEWorldsWhen(tickCountExceedsTheLimit);
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

void FSimplePIETestBase::resetTickCount()
{
	tickCount = 0;
}


#endif //WITH_DEV_AUTOMATION_TESTS
