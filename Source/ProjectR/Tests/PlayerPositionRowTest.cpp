// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "PlayerPositionRowTest.h"
#include "UI/PlayerPositionRow.h"

bool FUPlayerPositionRowIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UPlayerPositionRow* testRow = NewObject<UPlayerPositionRow>();

	TestNotNull(FString("Shouldn't be null when instantiated"), testRow);

	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS