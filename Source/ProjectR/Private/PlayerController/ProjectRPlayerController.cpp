// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/ProjectRPlayerController.h"
#include "UI/PauseMenu.h"
#include "Kismet/GameplayStatics.h"

void AProjectRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindKey(EKeys::Escape, IE_Pressed, this, &AProjectRPlayerController::loadPauseMenuWrapper);
}

AProjectRPlayerController::AProjectRPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bShouldPerformFullTickWhenPaused = true;
}

UPauseMenu* AProjectRPlayerController::loadPauseMenu()
{
	if (!pauseMenu)
	{
		pauseMenu = CreateWidget<UPauseMenu>(GetWorld()->GetGameInstance(), pauseMenuClass, FName("Pause Menu"));
	}
	if (!pauseMenu->IsInViewport())
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		pauseMenu->AddToViewport();
		bShowMouseCursor = true;
	}
	else
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		pauseMenu->RemoveFromViewport();
		bShowMouseCursor = false;
	}

	return pauseMenu;
}

void AProjectRPlayerController::loadPauseMenuWrapper()
{
	loadPauseMenu();
}
