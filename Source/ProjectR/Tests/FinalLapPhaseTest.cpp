// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "FinalLapPhaseTest.h"
#include "LapPhases/FinalLapPhase.h"
#include "LapPhases/InitialLapPhase.h"


bool FAFinalLapPhaseIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AFinalLapPhase* testFinalPhase = NewObject<AFinalLapPhase>();

	TestNotNull(TEXT("The final lap phase shouldn't be null after instantiating it."), testFinalPhase);

	return true;
}


bool FAFinalLapPhaseUpdateStateReturnsInitialLapPhaseIfItsPassedAsParameterTest::RunTest(const FString& Parameters)
{
	AFinalLapPhase* testFinalLapPhase = NewObject<AFinalLapPhase>();
	AInitialLapPhase* testInitialLapPhase = NewObject<AInitialLapPhase>();

	TestTrue(TEXT("The final lap phase should return the InitialLapPhase instance if that is passed as parameter."), testFinalLapPhase->updatePhase(testInitialLapPhase) == testInitialLapPhase);

	return true;
}


bool FAFinalLapPhaseUpdateStateReturnsItselfIfInitialLapPhaseIsntPassedAsParameterTest::RunTest(const FString& Parameters)
{
	AFinalLapPhase* testFinalPhase = NewObject<AFinalLapPhase>();
	ALapPhase* parameter = NewObject<ALapPhase>();
	bool isntInitialLapPhase = parameter->GetClass() != AInitialLapPhase::StaticClass();

	TestTrue(TEXT("The final phase should return itself if a InitialLapPhase instance isn't passed as parameter of updateState."), isntInitialLapPhase && testFinalPhase->updatePhase(parameter) == testFinalPhase);

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS