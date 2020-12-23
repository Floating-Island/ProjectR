// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkCommands.h"

#include "LevelEditor.h"
#include "Editor/UnrealEdEngine.h"
#include "UnrealEdGlobals.h"

NetworkCommands::NetworkCommands()
{
}

NetworkCommands::~NetworkCommands()
{
}








bool FStartNetworkedPIESession::Update()
{
	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	
	ULevelEditorPlaySettings* playSettings =  GetMutableDefault<ULevelEditorPlaySettings>();
	playSettings->SetPlayNumberOfClients(numParticipants);
	playSettings->SetPlayNetMode(netMode);

	FRequestPlaySessionParams sessionParameters;
	sessionParameters.DestinationSlateViewport = LevelEditorModule.GetFirstActiveViewport();//sets the server viewport in there. Otherwise, a window is created for the server.
	sessionParameters.EditorPlaySettings = playSettings;	

	GUnrealEd->RequestPlaySession(sessionParameters);
	
	return true;
}