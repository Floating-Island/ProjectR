// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "JetMOCKTest.h"
#include "Mocks/JetMOCK.h"


bool FJetMOCKIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AJetMOCK* testMockJet = NewObject<AJetMOCK>();

	TestNotNull(TEXT("The JetMOCK shouldn't be null after instantiating it."), testMockJet);

	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS