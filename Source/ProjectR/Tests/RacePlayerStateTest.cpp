// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "RacePlayerStateTest.h"
#include "PlayerState/RacePlayerState.h"


bool FARacePlayerStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ARacePlayerState* testPlayerState = NewObject<ARacePlayerState>();

	TestTrue(TEXT("Shouldn't be null when instantiated"), testPlayerState);
	
	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS