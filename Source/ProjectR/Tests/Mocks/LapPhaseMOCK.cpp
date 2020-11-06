// Fill out your copyright notice in the Description page of Project Settings.


#include "LapPhaseMOCK.h"

bool ALapPhaseMOCK::hasAStaticMesh()
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
