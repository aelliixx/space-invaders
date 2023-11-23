// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders


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
	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(NameEntryWidget->TakeWidget());
	GetOwningPlayer()->SetInputMode(InputMode);
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

	if (CrabClass)
		CrabPoints->SetText(FText::Format(FText::FromString("= x{0}"), FText::FromString(
			                                  FString::FromInt(
				                                  CrabClass.GetDefaultObject()->GetPointWorth()
			                                  )
		                                  )
		));
	if (OctopusClass)
		OctopusPoints->SetText(FText::Format(FText::FromString("= x{0}"), FText::FromString(
			                                     FString::FromInt(
				                                     OctopusClass.GetDefaultObject()->GetPointWorth()
			                                     )
		                                     )
		));
}
