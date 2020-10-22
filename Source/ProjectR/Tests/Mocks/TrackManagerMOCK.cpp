// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackManagerMOCK.h"

TSet<ATrackGenerator*> ATrackManagerMOCK::trackGenerators()
{
	return trackGeneratorSet;
}

bool ATrackManagerMOCK::hasJetsStored()
{
	return jetsToMagnetize.Num() > 0 ? true : false;
}
