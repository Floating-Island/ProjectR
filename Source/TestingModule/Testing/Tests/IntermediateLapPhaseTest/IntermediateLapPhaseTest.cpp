// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "IntermediateLapPhaseTest.h"
#include "LapPhases/IntermediateLapPhase.h"
#include "LapPhases/FinalLapPhase.h"


bool FAIntermediateLapPhaseIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AIntermediateLapPhase* testIntermediatePhase = NewObject<AIntermediateLapPhase>();

	TestNotNull(TEXT("The intermediate lap phase shouldn't be null after instantiating it."), testIntermediatePhase);

	return true;
}


bool FAIntermediateLapPhaseUpdateStateReturnsFinalLapPhaseIfItsPassedAsParameterTest::RunTest(const FString& Parameters)
{
	AIntermediateLapPhase* testIntermediateLapPhase = NewObject<AIntermediateLapPhase>();
	AFinalLapPhase* testFinalLapPhase = NewObject<AFinalLapPhase>();

	TestTrue(TEXT("The intermediate lap phase should return the FinalLapPhase instance if that is passed as parameter of updateState."), testIntermediateLapPhase->updatePhase(testFinalLapPhase) == testFinalLapPhase);

	return true;
}


bool FAIntermediateLapPhaseUpdateStateReturnsItselfIfFinalLapPhaseIsntPassedAsParameterTest::RunTest(const FString& Parameters)
{
	AIntermediateLapPhase* testIntermediatePhase = NewObject<AIntermediateLapPhase>();
	ALapPhase* parameter = NewObject<ALapPhase>();
	bool isntFinalLapPhase = parameter->GetClass() != AFinalLapPhase::StaticClass();
	
	TestTrue(TEXT("The intermediate phase should return itself if a FinalLapPhase instance isn't passed as parameter of updateState."), isntFinalLapPhase && testIntermediatePhase->updatePhase(parameter) == testIntermediatePhase);

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS