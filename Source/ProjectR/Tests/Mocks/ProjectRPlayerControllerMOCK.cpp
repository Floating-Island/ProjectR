// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectRPlayerControllerMOCK.h"
#include "UI/PauseMenu.h"

bool AProjectRPlayerControllerMOCK::pauseMenuIsInViewport()
{
	if(pauseMenu && pauseMenu->IsInViewport())
	{
		return true;
	}
	return false;
}
