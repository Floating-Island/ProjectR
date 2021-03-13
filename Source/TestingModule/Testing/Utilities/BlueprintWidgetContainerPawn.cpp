// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintWidgetContainerPawn.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ABlueprintWidgetContainerPawn::ABlueprintWidgetContainerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	widget = nullptr;
}

// Called when the game starts or when spawned
void ABlueprintWidgetContainerPawn::BeginPlay()
{
	Super::BeginPlay();
	if(widgetClass)
	{
		widget = UUserWidget::CreateWidgetInstance(*GetWorld(), widgetClass, FName("Widget instance"));
	}
}

UUserWidget* ABlueprintWidgetContainerPawn::retrieveWidget()
{
	return widget;
}

