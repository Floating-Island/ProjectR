// Fill out your copyright notice in the Description page of Project Settings.


#include "PIESessionUtilities.h"
//to be able to process inputs:
#include "GameFramework/PlayerInput.h"
#include "GameFramework/GameModeBase.h"

PIESessionUtilities::PIESessionUtilities()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		throw "Can't use this class when no PIE session is in progress!!";
	}
	pieWorld = GEditor->GetPIEWorldContext()->World();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
}

PIESessionUtilities::~PIESessionUtilities()
{
}

UWorld* PIESessionUtilities::defaultPIEWorld()
{
	return pieWorld;
}

UWorld* PIESessionUtilities::currentPIEWorld()
{
	return GEditor->GetPIEWorldContext()->World();
}

void PIESessionUtilities::spawnLocalPlayer()
{
	AGameModeBase* testGameMode = pieWorld->GetAuthGameMode();

	testGameMode->SpawnPlayerFromSimulate(FVector(0), FRotator(0));//spawns a player with controller and the default pawn set in the world game mode.
}

void PIESessionUtilities::processLocalPlayerInputFrom(FName anAxisMappingName)
{
	AGameModeBase* testGameMode = pieWorld->GetAuthGameMode();

	APlayerController* controller = Cast<APlayerController, AActor>(testGameMode->GetGameInstance()->GetFirstLocalPlayerController(pieWorld));

	processKeyPressFrom(anAxisMappingName, controller);
}

void PIESessionUtilities::processKeyPressFrom(FName anAxisMappingName, APlayerController* aController)
{
	FName const actionName = anAxisMappingName;
	TArray<FInputAxisKeyMapping> axisMappings = aController->PlayerInput->GetKeysForAxis(actionName);//in the editor, we are going to add a new axis mapping inside Project settings -> Input
	//in the pawn class, we are going to add a player input binding with:
	//	PlayerInputComponent->BindAxis("AxisMappingName",this, &YourPawn::actionToBind);
	//and in the constructor:
	//AutoPossessPlayer = EAutoReceiveInput::Player0;//this should be changed when we start doing multiplayer. It won't work.
	FKey actionKey;
	for (auto axisMap : axisMappings)
	{
		if (axisMap.Scale > 0)
		{
			actionKey = axisMap.Key;
			break;
		}
	}

	aController->InputKey(actionKey, EInputEvent::IE_Repeat, 5.0f, false);
}

void PIESessionUtilities::processLocalPlayerActionInputFrom(FName anActionMappingName)
{
	AGameModeBase* testGameMode = pieWorld->GetAuthGameMode();

	APlayerController* controller = Cast<APlayerController, AActor>(testGameMode->GetGameInstance()->GetFirstLocalPlayerController(pieWorld));

	processActionKeyPressFrom(anActionMappingName, controller);
}

void PIESessionUtilities::processActionKeyPressFrom(FName anActionMappingName, APlayerController* aController)
{
	FName const actionName = anActionMappingName;
	TArray<FInputActionKeyMapping> actionMappings = aController->PlayerInput->GetKeysForAction(actionName);//in the editor, we are going to add a new action mapping inside Project settings -> Input
	//in the pawn class, we are going to add a player input binding with:
	//	PlayerInputComponent->BindAction("ActionMappingName", EInputEvent::IE_Pressed, this, &YourPawn::actionToBind);
	//and in the constructor:
	//AutoPossessPlayer = EAutoReceiveInput::Player0;//this should be changed when we start doing multiplayer. It won't work.

	for(const auto& action : actionMappings)
	{
		UE_LOG(LogTemp, Log, TEXT("Pressing key: %s."), *action.Key.ToString());
		aController->InputKey(action.Key, EInputEvent::IE_Pressed, 5.0f, false);
	}
}

void PIESessionUtilities::processLocalPlayerActionInputReleaseFrom(FName anActionMappingName)
{
	AGameModeBase* testGameMode = pieWorld->GetAuthGameMode();

	APlayerController* controller = Cast<APlayerController, AActor>(testGameMode->GetGameInstance()->GetFirstLocalPlayerController(pieWorld));

	processActionKeyReleaseFrom(anActionMappingName, controller);
}

void PIESessionUtilities::processActionKeyReleaseFrom(FName anActionMappingName, APlayerController* aController)
{
	FName const actionName = anActionMappingName;
	TArray<FInputActionKeyMapping> actionMappings = aController->PlayerInput->GetKeysForAction(actionName);//in the editor, we are going to add a new action mapping inside Project settings -> Input
	//in the pawn class, we are going to add a player input binding with:
	//	PlayerInputComponent->BindAction("ActionMappingName", EInputEvent::IE_Released, this, &YourPawn::actionToBind);
	//and in the constructor:
	//AutoPossessPlayer = EAutoReceiveInput::Player0;//this should be changed when we start doing multiplayer. It won't work.

	for(const auto& action : actionMappings)
	{
		UE_LOG(LogTemp, Log, TEXT("Releasing key: %s."), *action.Key.ToString());
		aController->InputKey(action.Key, EInputEvent::IE_Released, 5.0f, false);
	}
}

void PIESessionUtilities::processEditorClick(FVector2D atCoordinates)
{
	//Get our slate application
	FSlateApplication& slateApplication = FSlateApplication::Get();

	const TSet<FKey> pressedButtons = TSet<FKey>({ EKeys::LeftMouseButton });

	FPointerEvent mouseMoveAndClickEvent(
		0,
		slateApplication.CursorPointerIndex,
		atCoordinates,
		FVector2D(0, 0),
		pressedButtons,
		EKeys::LeftMouseButton,
		0,
		slateApplication.GetPlatformApplication()->GetModifierKeys()
	);
	TSharedPtr<FGenericWindow> genericWindow;
	/*
	 *It's not necessary to move before clicking because when using process mouse button double click, it also moves the cursor to the desired position.
	 *UE_LOG(LogTemp, Log, TEXT("Attempting a mouse move:"));
	 *bool mouseMove = SlateApp.ProcessMouseMoveEvent(mouseMoveAndClickEvent);
	 *UE_LOG(LogTemp, Log, TEXT("a mouse move %s been done."), *FString(mouseMove ? "has" : "hasn't"));
	*/
	UE_LOG(LogTemp, Log, TEXT("Attempting click at coordinates: %s."), *atCoordinates.ToString());
	bool mouseClick = slateApplication.ProcessMouseButtonDoubleClickEvent(genericWindow, mouseMoveAndClickEvent);
	UE_LOG(LogTemp, Log, TEXT("a mouse click %s been done."), *FString(mouseClick ? "has" : "hasn't"));
}

void PIESessionUtilities::processEditorClickAtWindow(FVector2D atCoordinates, TSharedPtr<FGenericWindow> aWindow)
{
	//Get our slate application
	FSlateApplication& slateApplication = FSlateApplication::Get();

	const TSet<FKey> pressedButtons = TSet<FKey>({ EKeys::LeftMouseButton });

	FPointerEvent mouseMoveAndClickEvent(
		0,
		slateApplication.CursorPointerIndex,
		atCoordinates,
		FVector2D(0, 0),
		pressedButtons,
		EKeys::LeftMouseButton,
		0,
		slateApplication.GetPlatformApplication()->GetModifierKeys()
	);

	aWindow->BringToFront();
	
	/*
	 *It's not necessary to move before clicking because when using process mouse button double click, it also moves the cursor to the desired position.
	 *UE_LOG(LogTemp, Log, TEXT("Attempting a mouse move:"));
	 *bool mouseMove = SlateApp.ProcessMouseMoveEvent(mouseMoveAndClickEvent);
	 *UE_LOG(LogTemp, Log, TEXT("a mouse move %s been done."), *FString(mouseMove ? "has" : "hasn't"));
	*/
	UE_LOG(LogTemp, Log, TEXT("Attempting click at coordinates: %s."), *atCoordinates.ToString());
	bool mouseClick = slateApplication.ProcessMouseButtonDoubleClickEvent(aWindow, mouseMoveAndClickEvent);
	UE_LOG(LogTemp, Log, TEXT("a mouse click %s been done."), *FString(mouseClick ? "has" : "hasn't"));
}
