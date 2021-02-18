// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ScrollBox.h"
#include "StringButtonScrollBox.generated.h"

class UStringHolderButton;
/**
 * 
 */
UCLASS()
class PROJECTR_API UStringButtonScrollBox : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
		UScrollBox* scrollBoxWidget;

	UPROPERTY()
		UStringHolderButton* selectedChild;
	
	UPROPERTY(EditDefaultsOnly, Category = "String Holder Button Class")
		TSubclassOf<UStringHolderButton> stringHolderButtonClass;

	
public:
	virtual bool Initialize() override;
	void populateBoxWith(TArray<FString> aBunchOfStrings);
	int stringButtonsQuantity();
	FString selectedString();
	void childClicked(UStringHolderButton* aChild);
};
