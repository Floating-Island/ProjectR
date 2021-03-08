// Fill out your copyright notice in the Description page of Project Settings.


#include "LapPhaseMOCK.h"

bool ALapPhaseMOCK::hasAStaticMeshComponent()
{
	return phaseWall ? true : false;
}

bool ALapPhaseMOCK::hasAStaticMeshAssociated()
{
	return phaseWall->GetStaticMesh() ? true : false;
}

bool ALapPhaseMOCK::phaseWallIsRootComponent()
{
	return phaseWall == RootComponent ? true : false;
}

bool ALapPhaseMOCK::hasCollisionEnabledToQueryOnly()
{
	return RootComponent->GetCollisionEnabled() == ECollisionEnabled::QueryOnly ? true : false;
}

bool ALapPhaseMOCK::overlapsWithPawnChannel()
{
	return RootComponent->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) == ECR_Overlap ? true : false;
}

bool ALapPhaseMOCK::objectTypeIsWorldStatic()
{
	return RootComponent->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic ? true : false;
}

bool ALapPhaseMOCK::generatesOverlapEvents()
{
	return phaseWall->GetGenerateOverlapEvents();
}

bool ALapPhaseMOCK::IsHiddenInGame()
{
	return phaseWall->bHiddenInGame;
}
