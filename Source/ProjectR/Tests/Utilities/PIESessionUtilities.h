// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class AJet;
class AJetMOCK;

/**
 * This class is intended to use in tests only and when the editor is playing a PIE session
 */
class PROJECTR_API PIESessionUtilities
{
public:
	PIESessionUtilities();
	~PIESessionUtilities();
	static UWorld* currentPIEWorld();
	static AJet* spawnJetInPIE(FVector location = FVector());
	static AJetMOCK* spawnJetMOCKInPIE(FVector location = FVector());
};
