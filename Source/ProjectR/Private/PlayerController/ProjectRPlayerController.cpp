// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/ProjectRPlayerController.h"

#include "PlayerState/RacePlayerState.h"
#include "UI/PauseMenu.h"
#include "Kismet/GameplayStatics.h"
#include "UI/RacePlayerUI.h"
#include "TimerManager.h"

void AProjectRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindKey(EKeys::Escape, IE_Pressed, this, &AProjectRPlayerController::loadPauseMenuWrapper);
}

void AProjectRPlayerController::showRaceUI()
{
	raceUI->AddToPlayerScreen();
}

void AProjectRPlayerController::configureRaceUI()
{
	ARacePlayerState* racePlayerState = Cast<ARacePlayerState, APlayerState>(PlayerState);
	racePlayerState->subscribeToLapUpdate(raceUI);
	racePlayerState->subscribeToPositionUpdate(raceUI);
	racePlayerState->fireEvents(this);
	raceUI->setTotalLapsTo(racePlayerState->totalLaps());
}

AProjectRPlayerController::AProjectRPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bShouldPerformFullTickWhenPaused = true;
}

UPauseMenu* AProjectRPlayerController::loadPauseMenu()
{//if someday there's a crash when bringing up the pause menu, look at the main menu and singleplayer menu instantiation in the game instance.
	if (!pauseMenu || pauseMenu->IsUnreachable())
	{
		pauseMenu = CreateWidget<UPauseMenu>(GetWorld(), pauseMenuClass, FName("Pause Menu"));
	}
	if (!pauseMenu->IsInViewport())
	{
		focusOnPauseMenu();
	}
	else
	{
		focusOnGame(); 
	}

	return pauseMenu;
}

void AProjectRPlayerController::focusOnPauseMenu()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	pauseMenu->AddToViewport();
	FInputModeGameAndUI inputModeData;
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModeData.SetWidgetToFocus(pauseMenu->TakeWidget());
	SetInputMode(inputModeData);
	bShowMouseCursor = true;
}

void AProjectRPlayerController::loadRaceUI_Implementation()
{
	if(IsLocalPlayerController())
	{
		ARacePlayerState* racePlayerState = Cast<ARacePlayerState, APlayerState>(PlayerState);
		if(racePlayerState)
		{
			UClass* raceUIClass = racePlayerState->raceUIType();
			if (!raceUI || raceUI->IsUnreachable())
			{
				raceUI = CreateWidget<URacePlayerUI>(this, raceUIClass);
				configureRaceUI();
			}
			if (!raceUI->IsInViewport())
			{
				showRaceUI();
			}
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AProjectRPlayerController::loadRaceUI);
		}
	}
}

void AProjectRPlayerController::focusOnGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	pauseMenu->RemoveFromViewport();
	FInputModeGameOnly inputModeData;
	inputModeData.SetConsumeCaptureMouseDown(true);
	SetInputMode(inputModeData);
	bShowMouseCursor = false;
}

void AProjectRPlayerController::loadPauseMenuWrapper()
{
	loadPauseMenu();
}
