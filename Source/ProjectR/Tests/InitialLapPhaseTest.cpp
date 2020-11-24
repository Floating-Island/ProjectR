// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "InitialLapPhaseTest.h"
#include "LapPhases/InitialLapPhase.h"
#include "LapPhases/IntermediateLapPhase.h"


bool FAInitialLapPhaseIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AInitialLapPhase* testInitialPhase = NewObject<AInitialLapPhase>();

	TestNotNull(TEXT("The initial phase shouldn't be null after instantiating it."), testInitialPhase);

	return true;
}


bool FAInitialLapPhaseUpdateStateReturnsIntermediateLapPhaseIfItsPassedAsParameterTest::RunTest(const FString& Parameters)
{
	AInitialLapPhase* testInitialPhase = NewObject<AInitialLapPhase>();
	AIntermediateLapPhase* testIntermediateLapPhase = NewObject<AIntermediateLapPhase>();

	TestTrue(TEXT("The initial phase should return the IntermediateLapPhase instance if that is passed as parameter of updateState."), testInitialPhase->updatePhase(testIntermediateLapPhase) == testIntermediateLapPhase);

	return true;
}


bool FAInitialLapPhaseUpdateStateReturnsItselfIfIntermediateLapPhaseIsntPassedAsParameterTest::RunTest(const FString& Parameters)
{
	AInitialLapPhase* testInitialPhase = NewObject<AInitialLapPhase>();
	ALapPhase* parameter = NewObject<ALapPhase>();
	bool isntIntermediateLapPhase = parameter->GetClass() != AIntermediateLapPhase::StaticClass();
	
	TestTrue(TEXT("The initial phase should return itself if a IntermediateLapPhase instance isn't passed as parameter of updateState."), isntIntermediateLapPhase && testInitialPhase->updatePhase(parameter) == testInitialPhase);

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS