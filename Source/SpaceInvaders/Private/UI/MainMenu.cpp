// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"

#include "Kismet/KismetSystemLibrary.h"
#include "UI/NameEntry.h"


void UMainMenu::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}

void UMainMenu::StartGame()
{
	const auto NameEntryWidget = CreateWidget(this, NameEntryWidgetClass);
	NameEntryWidget->AddToViewport();
}

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UNameEntry> NameEntry(TEXT("/Game/SpaceInvaders/UI/W_NameEntry"));
	NameEntryWidgetClass = NameEntry.Class;
}

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	StartGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::StartGame);
	QuitGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::QuitGame);
}
