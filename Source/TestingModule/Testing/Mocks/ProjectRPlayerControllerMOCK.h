// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerController/ProjectRPlayerController.h"
#include "ProjectRPlayerControllerMOCK.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGMODULE_API AProjectRPlayerControllerMOCK : public AProjectRPlayerController
{
	GENERATED_BODY()
public:
	bool pauseMenuIsInViewport();
	
};
