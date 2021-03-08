// Fill out your copyright notice in the Description page of Project Settings.






#if WITH_DEV_AUTOMATION_TESTS

#include "LapPhaseTestCommands.h"
#include "LapPhases/LapPhase.h"
#include "../../Mocks/LapPhaseMOCK.h"

#include "Kismet/GameplayStatics.h"



//Test preparation commands:











//Test check commands:


bool FCheckLapPhaseCollisionEnabled::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ALapPhaseMOCK* testPhase = Cast<ALapPhaseMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ALapPhaseMOCK::StaticClass()));
	if (testPhase)
	{

		bool collisionIsQueryOnly = testPhase->hasCollisionEnabledToQueryOnly();
		UE_LOG(LogTemp, Log, TEXT("The phase wall has collision enabled to query only: %s."), *FString(collisionIsQueryOnly ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the phase wall should have collision enabled to query only."), collisionIsQueryOnly);
		return true;
	}
	return false;
}


bool FCheckLapPhaseCollisionResponse::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ALapPhaseMOCK* testPhase = Cast<ALapPhaseMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ALapPhaseMOCK::StaticClass()));
	if (testPhase)
	{

		bool overlapsWithPawnChannel = testPhase->overlapsWithPawnChannel();
		UE_LOG(LogTemp, Log, TEXT("The lap phase overlaps with the pawn channel: %s."), *FString(overlapsWithPawnChannel ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the lap phase should overlap with the pawn channel."), overlapsWithPawnChannel);
		return true;
	}
	return false;
}


bool FCheckLapPhaseObjectType::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ALapPhaseMOCK* testPhase = Cast<ALapPhaseMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ALapPhaseMOCK::StaticClass()));
	if (testPhase)
	{

		bool objectTypeIsWorldStatic = testPhase->objectTypeIsWorldStatic();
		UE_LOG(LogTemp, Log, TEXT("The lap phase object type is world static: %s."), *FString(objectTypeIsWorldStatic ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the lap phase object type should be world static."), objectTypeIsWorldStatic);
		return true;
	}
	return false;
}


bool FCheckLapPhaseOverlapEvents::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ALapPhaseMOCK* testPhase = Cast<ALapPhaseMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ALapPhaseMOCK::StaticClass()));
	if (testPhase)
	{

		bool generatesOverlapEvents = testPhase->generatesOverlapEvents();
		UE_LOG(LogTemp, Log, TEXT("The lap phase generates overlap events: %s."), *FString(generatesOverlapEvents ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the lap phase should generate overlap events."), generatesOverlapEvents);
		return true;
	}
	return false;
}

#endif //WITH_DEV_AUTOMATION_TESTS
