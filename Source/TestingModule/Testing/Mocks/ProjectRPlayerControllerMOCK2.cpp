// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectRPlayerControllerMOCK2.h"
#include "UI/PauseMenu.h"

bool AProjectRPlayerControllerMOCK2::pauseMenuIsInViewport()
{
	if(pauseMenu && pauseMenu->IsInViewport())
	{
		return true;
	}
	return false;
}