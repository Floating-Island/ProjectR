// Fill out your copyright notice in the Description page of Project Settings.






#if WITH_DEV_AUTOMATION_TESTS

#include "TrackGeneratorTestCommands.h"
#include "Track/TrackGenerator.h"
#include "../../Mocks/TrackGeneratorMOCK.h"
#include "Track/TrackManager.h"

#include "Editor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

#include "../../Utilities/PIESessionUtilities.h"

//Test preparation commands:


bool FSpawnTrackGeneratorInEditorWorldRollSplineComponents::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = testWorld->SpawnActor<ATrackGeneratorMOCK>(ATrackGeneratorMOCK::StaticClass());

	testGenerator->rollSplines(rollValue);

	return true;
}


bool FSpawnTrackGeneratorInEditorWorldWidenSplineComponents::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = testWorld->SpawnActor<ATrackGeneratorMOCK>(ATrackGeneratorMOCK::StaticClass());

	testGenerator->widenSplines(widthValue);

	return true;
}


bool FSpawnTrackGeneratorInEditorWorldDisableCollisions::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = testWorld->SpawnActor<ATrackGeneratorMOCK>(ATrackGeneratorMOCK::StaticClass());

	testGenerator->disableCollisions();

	return true;
}


bool FRetrieveTrackGeneratorInEditorWorldRollSplineComponents::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "BoundedTrackGeneratorMOCKWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));

	testGenerator->rollSplines(rollValue);

	return true;
}


bool FRetrieveTrackGeneratorInEditorWorldWidenSplineComponents::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "BoundedTrackGeneratorMOCKWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));

	testGenerator->widenSplines(widthValue);

	return true;
}


bool FRetrieveTrackGeneratorInEditorDisableCollisions::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "BoundedTrackGeneratorMOCKWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));

	testGenerator->disableCollisions();

	return true;
}









//Test check commands:


bool FCheckRoadSplinesQuantity::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{
		int32 roadSplinesQuantity = testGenerator->roadSplinesQuantity();
		int32 splinePointsQuantity = testGenerator->splinePointsQuantity();
		bool sameAmountOfSplinePointsAsRoadSplines = roadSplinesQuantity == splinePointsQuantity;//splines always have start and end points at the beginning...
		UE_LOG(LogTemp, Log, TEXT("Spline points quantity in generator: %d."), splinePointsQuantity);
		UE_LOG(LogTemp, Log, TEXT("Road splines quantity in generator: %d."), roadSplinesQuantity);
		UE_LOG(LogTemp, Log, TEXT("Road splines quantity is coincident with number of spline points: %s."), *FString(sameAmountOfSplinePointsAsRoadSplines ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the number of road splines should be coincident with the spline points quantity."), sameAmountOfSplinePointsAsRoadSplines);
		return true;
	}
	return false;
}


bool FCheckRoadSplinesStartPositions::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesStartPositionsMatchSplinePoints = testGenerator->roadSplinesAndPointsHaveSameStartPositions();
		UE_LOG(LogTemp, Log, TEXT("Road splines start positions are coincident with the positions of spline points: %s."), *FString(roadSplinesStartPositionsMatchSplinePoints ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the start positions of road splines should be coincident with the spline points positions."), roadSplinesStartPositionsMatchSplinePoints);
		return true;
	}
	return false;
}


bool FCheckRoadSplinesEndPositions::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesEndPositionsMatchSplinePoints = testGenerator->roadSplinesAndPointsHaveSameEndPositions();
		UE_LOG(LogTemp, Log, TEXT("Road splines end positions are coincident with the positions of next spline points: %s."), *FString(roadSplinesEndPositionsMatchSplinePoints ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the end positions of road splines should be coincident with the next spline points positions."), roadSplinesEndPositionsMatchSplinePoints);
		return true;
	}
	return false;
}


bool FCheckRoadSplinesStartTangents::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesStartTangentsMatchSplinePoints = testGenerator->roadSplinesAndPointsHaveSameStartTangents();
		UE_LOG(LogTemp, Log, TEXT("Road splines start tangents are coincident with the tangents of spline points: %s."), *FString(roadSplinesStartTangentsMatchSplinePoints ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the start tangents of road splines should be coincident with the spline points tangents."), roadSplinesStartTangentsMatchSplinePoints);
		return true;
	}
	return false;
}


bool FCheckRoadSplinesEndTangents::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesEndTangentsMatchNextSplinePoints = testGenerator->roadSplinesAndPointsHaveSameEndTangents();
		UE_LOG(LogTemp, Log, TEXT("Road splines end tangents are coincident with the tangents of next spline points: %s."), *FString(roadSplinesEndTangentsMatchNextSplinePoints ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the end tangents of road splines should be coincident with the next spline points tangents."), roadSplinesEndTangentsMatchNextSplinePoints);
		return true;
	}
	return false;
}


bool FCheckRoadSplinesMeshes::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesHaveMeshesSet = testGenerator->roadSplinesHaveMeshesSet();
		UE_LOG(LogTemp, Log, TEXT("Road splines meshes are set: %s."), *FString(roadSplinesHaveMeshesSet ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the road splines meshes should be set."), roadSplinesHaveMeshesSet);
		return true;
	}
	return false;
}


bool FCheckRoadSplinesMeshesAreRoadMesh::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesHaveMeshesSetAsRoadMesh = testGenerator->roadSplinesMeshesAreRoadMesh();
		UE_LOG(LogTemp, Log, TEXT("Road splines meshes are the road mesh: %s."), *FString(roadSplinesHaveMeshesSetAsRoadMesh ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the road splines meshes should be the road mesh."), roadSplinesHaveMeshesSetAsRoadMesh);
		return true;
	}
	return false;
}


bool FCheckSplineMagnetSplinesQuantity::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool splineHasSameNumberOfMagnetSplinesAsSplinePoints = testGenerator->magnetSplinesQuantitySameAsSplinePoints();
		UE_LOG(LogTemp, Log, TEXT("Has the same amount of spline points as magnet splines: %s."), *FString(splineHasSameNumberOfMagnetSplinesAsSplinePoints ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the spline should have the same amount of magnet splines as spline points."), splineHasSameNumberOfMagnetSplinesAsSplinePoints);
		return true;
	}
	return false;
}


bool FCheckRoadSplinesCollisionEnabled::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesHaveCollisionEnabledSetToQueryAndPhysics = testGenerator->roadSplinesHaveCollisionEnabledSetToQueryAndPhysics();
		UE_LOG(LogTemp, Log, TEXT("Road splines have collision enabled set to query and physics: %s."), *FString(roadSplinesHaveCollisionEnabledSetToQueryAndPhysics ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, Road splines should have collision enabled set to query and physics."), roadSplinesHaveCollisionEnabledSetToQueryAndPhysics);
		return true;
	}
	return false;
}


bool FCheckRoadSplinesCollisionObjectType::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesHaveCollisionObjectToWorldStatic = testGenerator->roadSplinesHaveCollisionObjectToWorldStatic();
		UE_LOG(LogTemp, Log, TEXT("Road splines have collision object type of world static: %s."), *FString(roadSplinesHaveCollisionObjectToWorldStatic ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, Road splines should have collision object type of world static."), roadSplinesHaveCollisionObjectToWorldStatic);
		return true;
	}
	return false;
}


bool FCheckRoadSplinesAttachToRoot::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesAreAttachedToRoot = testGenerator->roadSplinesAreAttachedToRoot();
		UE_LOG(LogTemp, Log, TEXT("Road splines are attached to root component: %s."), *FString(roadSplinesAreAttachedToRoot ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, Road splines should be attached to root component."), roadSplinesAreAttachedToRoot);
		return true;
	}
	return false;
}


bool FCheckRoadSplinesMobility::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool roadSplinesMobilitySameAsRoot = testGenerator->roadSplinesMobilitySameAsRoot();
		UE_LOG(LogTemp, Log, TEXT("Road splines have the same mobility as the root component: %s."), *FString(roadSplinesMobilitySameAsRoot ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, Road splines should have the same mobility as the root component."), roadSplinesMobilitySameAsRoot);
		return true;
	}
	return false;
}


bool FCheckMagnetSplinesMobility::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetSplinesMobilitySameAsRoadSplines = testGenerator->magnetSplinesMobilitySameAsRoadSplines();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines have the same mobility as road splines: %s."), *FString(magnetSplinesMobilitySameAsRoadSplines ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, magnet splines should have the same mobility as road splines."), magnetSplinesMobilitySameAsRoadSplines);
		return true;
	}
	return false;
}


bool FCheckMagnetSplinesAttachToRoadSplines::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetSplinesAreAttachedToRoadSplines = testGenerator->magnetSplinesAreAttachedToRoadSplines();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines are attached to road splines: %s."), *FString(magnetSplinesAreAttachedToRoadSplines ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, magnet splines should be attached to road splines."), magnetSplinesAreAttachedToRoadSplines);
		return true;
	}
	return false;
}


bool FCheckMagnetSplinesOnTopRoadSplines::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetSplinesOnTopOfRoadSplines = testGenerator->magnetSplinesOnTopOfRoadSplines();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines are on top of road splines: %s."), *FString(magnetSplinesOnTopOfRoadSplines ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, magnet splines should be on top of road splines."), magnetSplinesOnTopOfRoadSplines);
		return true;
	}
	return false;
}


bool FCheckMagnetSplinesTangents::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetSplinesAndPointsHaveSameTangents = testGenerator->magnetSplinesAndPointsHaveSameTangents();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines tangents are coincident with the tangents of spline points: %s."), *FString(magnetSplinesAndPointsHaveSameTangents ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the tangents of magnet splines should be coincident with the spline points tangents."), magnetSplinesAndPointsHaveSameTangents);
		return true;
	}
	return false;
}


bool FCheckMagnetSplinesMeshes::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetSplinesHaveMeshesSet = testGenerator->magnetSplinesHaveMeshesSet();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines meshes are set: %s."), *FString(magnetSplinesHaveMeshesSet ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the magnet splines meshes should be set."), magnetSplinesHaveMeshesSet);
		return true;
	}
	return false;
}


bool FCheckMagnetSplinesVisibility::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetSplinesAreHiddenInGame = testGenerator->magnetSplinesAreHiddenInGame();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines are hidden in game: %s."), *FString(magnetSplinesAreHiddenInGame ? "true" : "false"));


		test->TestTrue(TEXT("The magnet splines should be set hidden in game."), magnetSplinesAreHiddenInGame);
		return true;
	}
	return false;
}


bool FCheckMagnetSplinesCollisionResponse::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool collisionEnabledToQueryOnlyOnMagnetSplines = testGenerator->collisionEnabledToQueryOnlyOnMagnetSplines();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines have collision enabled: %s."), *FString(collisionEnabledToQueryOnlyOnMagnetSplines ? "true" : "false"));


		test->TestTrue(TEXT("The magnet splines should have collision enabled."), collisionEnabledToQueryOnlyOnMagnetSplines);
		return true;
	}
	return false;
}


bool FCheckMagnetSplinesResponseToPawnChannel::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetSplinesOverlapWithPawnChannel = testGenerator->magnetSplinesOverlapWithPawnChannel();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines overlap with the pawn channel: %s."), *FString(magnetSplinesOverlapWithPawnChannel ? "true" : "false"));


		test->TestTrue(TEXT("The magnet splines should overlap with the pawn channel."), magnetSplinesOverlapWithPawnChannel);
		return true;
	}
	return false;
}


bool FCheckMagnetSplinesGenerateOverlapEvents::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool magnetSplinesGenerateOverlapEvents = testGenerator->magnetSplinesGenerateOverlapEvents();
		UE_LOG(LogTemp, Log, TEXT("Magnet splines generate overlap events: %s."), *FString(magnetSplinesGenerateOverlapEvents ? "true" : "false"));


		test->TestTrue(TEXT("The magnet splines should generate overlap events."), magnetSplinesGenerateOverlapEvents);
		return true;
	}
	return false;
}


bool FCheckComponentsSmoothInterpolation::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool componentsHaveSmoothInterpolation = testGenerator->componentsHaveSmoothInterpolation();
		UE_LOG(LogTemp, Log, TEXT("Components have smooth interpolation: %s."), *FString(componentsHaveSmoothInterpolation ? "true" : "false"));


		test->TestTrue(TEXT("The components should have smooth interpolation."), componentsHaveSmoothInterpolation);
		return true;
	}
	return false;
}


bool FCheckTrackSectionsArrayQuantityAdjustedToNumberOfSplinePoints::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool sameAmountOfTrackSectionsThanSplinePoints = testGenerator->sameAmountOfTrackSectionsThanSplinePoints();
		UE_LOG(LogTemp, Log, TEXT("The track sections array has the same number of elements as the number of spline points: %s."), *FString(sameAmountOfTrackSectionsThanSplinePoints ? "true" : "false"));


		test->TestTrue(TEXT("The track sections array should have the same number of elements as the number of spline points."), sameAmountOfTrackSectionsThanSplinePoints);
		return true;
	}
	return false;
}


bool FCheckComponentsRoll::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{
		bool componentsRollMatchSettedRoll = testGenerator->splineMeshComponentsRollIs(rollValue);
		UE_LOG(LogTemp, Log, TEXT("Components match setted roll: %s."), *FString(componentsRollMatchSettedRoll ? "true" : "false"));

		test->TestTrue(TEXT("The components should have their roll matching the one set."), componentsRollMatchSettedRoll);
		return true;
	}
	return false;
}


bool FCheckComponentsWidth::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{
		bool componentsWidthMatchSettedWidth = testGenerator->splineMeshComponentsWidthIs(widthValue);
		UE_LOG(LogTemp, Log, TEXT("Components match setted width: %s."), *FString(componentsWidthMatchSettedWidth ? "true" : "false"));

		test->TestTrue(TEXT("The components should have their width matching the one set."), componentsWidthMatchSettedWidth);
		return true;
	}
	return false;
}


bool FCheckComponentsCollision::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{
		bool componentsHavedCollisionsDisabled = testGenerator->splineMeshComponentsCollisionsDisabled();
		UE_LOG(LogTemp, Log, TEXT("Components match setted collision enable: %s."), *FString(componentsHavedCollisionsDisabled ? "true" : "false"));

		test->TestTrue(TEXT("The components should have their collision enable matching the one set."), componentsHavedCollisionsDisabled);
		return true;
	}
	return false;
}


bool FCheckComponentsExpectedCollisionInPIE::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();
		ATrackGeneratorMOCK* testGenerator = sessionUtilities.retrieveFromPIEAnInstanceOf<ATrackGeneratorMOCK>();
		if (testGenerator)
		{
			bool componentsHavedTheirExpectedCollisions = testGenerator->splineMeshComponentsExpectedCollisions();
			UE_LOG(LogTemp, Log, TEXT("Components have their collisions as expected: %s."), *FString(componentsHavedTheirExpectedCollisions ? "true" : "false"));

			test->TestTrue(TEXT("The components should have have their collisions as expected."), componentsHavedTheirExpectedCollisions);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}


bool FCheckTrackGeneratorSpawnsTrackManagerInPIE::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();
		ATrackGeneratorMOCK* testGenerator = sessionUtilities.retrieveFromPIEAnInstanceOf<ATrackGeneratorMOCK>();
		if (testGenerator)
		{
			ATrackManager* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ATrackManager>();
			UE_LOG(LogTemp, Log, TEXT("Track generator spawned a track manager: %s."), *FString(testManager ? "true" : "false"));

			test->TestNotNull(TEXT("The track generator should spawn a track manager at begin play."), testManager);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}


bool FCheckTrackGeneratorsSpawnOneTrackManagerInPIE::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();
		TArray<ATrackGenerator*> testGenerators = sessionUtilities.retrieveFromPIEAllInstancesOf<ATrackGenerator>();
		for (const auto& generator : testGenerators)
		{
			if (!generator)
			{
				return false;
			}
		}

		TArray<ATrackManager*> testManagers = sessionUtilities.retrieveFromPIEAllInstancesOf<ATrackManager>();
		bool onlyOneTrackManager = testManagers.Num() == 1 ? true : false;
		UE_LOG(LogTemp, Log, TEXT("Track generators in same world spawned only one track manager: %s."), *FString(onlyOneTrackManager? "true" : "false"));

		test->TestTrue(TEXT("The track generators should spawn only one track manager at begin play in the same world."), onlyOneTrackManager);
		testWorld->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckBoundsSplinesQuantity::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "BoundedTrackGeneratorMOCKWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{
		int32 boundsSplinesQuantity = testGenerator->boundsSplinesQuantity();
		int32 splinePointsQuantity = testGenerator->splinePointsQuantity();
		bool sameAmountOfSplinePointsAsBoundsSplines = boundsSplinesQuantity == splinePointsQuantity;//splines always have start and end points at the beginning...
		UE_LOG(LogTemp, Log, TEXT("Spline points quantity in generator: %d."), splinePointsQuantity);
		UE_LOG(LogTemp, Log, TEXT("Bounds splines quantity in generator: %d."), boundsSplinesQuantity);
		UE_LOG(LogTemp, Log, TEXT("Bounds splines quantity is coincident with number of spline points: %s."), *FString(sameAmountOfSplinePointsAsBoundsSplines ? "true" : "false"));

		test->TestTrue(TEXT("At spawning, the number of road splines should be coincident with the spline points quantity."), sameAmountOfSplinePointsAsBoundsSplines);
		return true;
	}
	return false;
}


bool FCheckBoundsSplinesAttachToRoadSplines::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "BoundedTrackGeneratorMOCKWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool boundsSplinesAreAttachedToRoadSplines = testGenerator->boundsSplinesAreAttachedToRoadSplines();
		UE_LOG(LogTemp, Log, TEXT("Bounds splines are attached to road splines: %s."), *FString(boundsSplinesAreAttachedToRoadSplines ? "true" : "false"));

		test->TestTrue(TEXT("At spawning, bounds splines should be attached to road splines."), boundsSplinesAreAttachedToRoadSplines);
		return true;
	}
	return false;
}


bool FCheckBoundsSplinesMobility::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "BoundedTrackGeneratorMOCKWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool boundsSplinesMobilitySameAsRoadSplines = testGenerator->boundsSplinesMobilitySameAsRoadSplines();
		UE_LOG(LogTemp, Log, TEXT("Bounds splines have the same mobility as road splines: %s."), *FString(boundsSplinesMobilitySameAsRoadSplines ? "true" : "false"));

		test->TestTrue(TEXT("At spawning, bounds splines should have the same mobility as road splines."), boundsSplinesMobilitySameAsRoadSplines);
		return true;
	}
	return false;
}


bool FCheckBoundsSplinesTangents::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "BoundedTrackGeneratorMOCKWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{
		bool boundsSplinesAndPointsHaveSameTangents = testGenerator->boundsSplinesAndPointsHaveSameTangents();
		UE_LOG(LogTemp, Log, TEXT("Bounds splines tangents are coincident with the tangents of spline points: %s."), *FString(boundsSplinesAndPointsHaveSameTangents ? "true" : "false"));

		test->TestTrue(TEXT("At spawning, the tangents of bounds splines should be coincident with the spline points tangents."), boundsSplinesAndPointsHaveSameTangents);
		return true;
	}
	return false;
}


bool FCheckBoundsSplinesMeshes::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "BoundedTrackGeneratorMOCKWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool boundsSplinesHaveMeshesSet = testGenerator->boundsSplinesHaveMeshesSet();
		UE_LOG(LogTemp, Log, TEXT("Bounds splines meshes are set: %s."), *FString(boundsSplinesHaveMeshesSet ? "true" : "false"));


		test->TestTrue(TEXT("At spawning, the bounds splines meshes should be set."), boundsSplinesHaveMeshesSet);
		return true;
	}
	return false;
}


bool FCheckBoundsSplinesVisibility::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "BoundedTrackGeneratorMOCKWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool boundsSplinesAreHiddenInGame = testGenerator->boundsSplinesAreHiddenInGame();
		UE_LOG(LogTemp, Log, TEXT("Bounds splines are hidden in game: %s."), *FString(boundsSplinesAreHiddenInGame ? "true" : "false"));


		test->TestTrue(TEXT("The bounds splines should be set hidden in game."), boundsSplinesAreHiddenInGame);
		return true;
	}
	return false;
}


bool FCheckBoundsSplinesSmoothInterpolation::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "BoundedTrackGeneratorMOCKWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool boundsSplinesHaveSmoothInterpolation = testGenerator->boundsSplinesHaveSmoothInterpolation();
		UE_LOG(LogTemp, Log, TEXT("Bounds splines have smooth interpolation: %s."), *FString(boundsSplinesHaveSmoothInterpolation ? "true" : "false"));


		test->TestTrue(TEXT("The bounds splines should be set to have smooth interpolation."), boundsSplinesHaveSmoothInterpolation);
		return true;
	}
	return false;
}


bool FCheckBoundSplinesRoll::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "BoundedTrackGeneratorMOCKWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool boundsSplinesHaveSameRoll = testGenerator->boundsSplinesHaveSameRollAs(rollValue);
		UE_LOG(LogTemp, Log, TEXT("Bounds splines have the same roll as %f: %s."), rollValue, *FString(boundsSplinesHaveSameRoll ? "true" : "false"));


		test->TestTrue(TEXT("The bounds splines should be set to have the same roll."), boundsSplinesHaveSameRoll);
		return true;
	}
	return false;
}


bool FCheckBoundSplinesWidth::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "BoundedTrackGeneratorMOCKWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{

		bool boundsSplinesHaveSameWidth = testGenerator->boundsSplinesHaveSameWidthAs(widthValue);
		UE_LOG(LogTemp, Log, TEXT("Bounds splines have the same width as %f: %s."), widthValue, *FString(boundsSplinesHaveSameWidth ? "true" : "false"));


		test->TestTrue(TEXT("The bounds splines should be set to have the same width."), boundsSplinesHaveSameWidth);
		return true;
	}
	return false;
}


bool FCheckBoundSplinesCollisionsDisabled::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "BoundedTrackGeneratorMOCKWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ATrackGeneratorMOCK* testGenerator = Cast<ATrackGeneratorMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGeneratorMOCK::StaticClass()));
	if (testGenerator)
	{
		bool BoundSplinesHavedCollisionsDisabled = testGenerator->boundsSplinesCollisionsDisabled();
		UE_LOG(LogTemp, Log, TEXT("bound splines match setted collision disabled: %s."), *FString(BoundSplinesHavedCollisionsDisabled ? "true" : "false"));

		test->TestTrue(TEXT("The bound splines should have their collision enable matching the one set."), BoundSplinesHavedCollisionsDisabled);
		return true;
	}
	return false;
}











#endif //WITH_DEV_AUTOMATION_TESTS
