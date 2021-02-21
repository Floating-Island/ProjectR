// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MapSelectorWidget.h"

#include "UI/StringButtonScrollBox.h"
#include "HAL/FileManager.h"

bool UMapSelectorWidget::Initialize()
{
	bool initializeResult = Super::Initialize();
	bIsFocusable = true;
	if(mapListing)
	{
		mapListing->bIsFocusable = true;
		createMapButtons();
	}
	return initializeResult;
}

TArray<FString> UMapSelectorWidget::mapsCollected()
{
	TArray<FString> mapPaths = TArray<FString>();
	IFileManager::Get().FindFilesRecursive(mapPaths, *FPaths::ProjectContentDir(), TEXT("*.umap"), true, false, false);

	TArray<FString> mapNames = TArray<FString>();

	for(FString mapPath : mapPaths)
	{
		//remove the path
		FString mapFile;
		FString discard;
		mapPath.Split(mapsDirectory, &discard, &mapFile);

		//remove the extension
		FString mapName;
		if(mapFile.Split(".", &mapName, &discard))
		{
			//add map name to the list
			mapNames.Add(mapName);
		}
	}
	return mapNames;
}

void UMapSelectorWidget::createMapButtons()
{
	TArray<FString> mapsFound = mapsCollected();
	mapListing->populateBoxWith(mapsFound);
}
