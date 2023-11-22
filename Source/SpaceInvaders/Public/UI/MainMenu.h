// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NameEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> StartGameButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> QuitGameButton;

	TSubclassOf<UNameEntry> NameEntryWidgetClass;

	UFUNCTION()
	void QuitGame();
	UFUNCTION()
	void StartGame();
	
public:

	UMainMenu(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;
};
