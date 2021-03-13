// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerController/ProjectRPlayerController.h"
#include "ProjectRPlayerControllerMOCK2.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGMODULE_API AProjectRPlayerControllerMOCK2 : public AProjectRPlayerController
{
	GENERATED_BODY()
public:
	bool pauseMenuIsInViewport();
	
};
