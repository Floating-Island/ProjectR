// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "ProjectRPlayerControllerTest.h"
#include "Commands/PrRPlayerControllerTestCommands.h"
#include "PlayerController/ProjectRPlayerController.h"





bool FAProjectRPlayerControllerIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AProjectRPlayerController* testPlayerController = NewObject<AProjectRPlayerController>();
	TestNotNull(TEXT("The player controller shouldn't be null after instantiating it."), testPlayerController);

	return true;
}






#endif //WITH_DEV_AUTOMATION_TESTS