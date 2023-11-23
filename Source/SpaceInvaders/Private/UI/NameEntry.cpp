// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders


#include "UI/NameEntry.h"

#include "SpaceInvadersGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Player/ShipController.h"

void UNameEntry::LoadGame()
{
	if (NameField->GetText().ToString().Len() == 0)
	{
		NameField->SetHintText(FText::FromString("Name is required"));
		return;
	}
	const auto Name = NameField->GetText().ToString();
	Cast<USpaceInvadersGameInstance>(GetGameInstance())->SetPlayerName(*Name);
	UGameplayStatics::OpenLevel(this, FName("SpaceInvadersLevel"), false);
}

void UNameEntry::Cancel()
{
	RemoveFromParent();
}

void UNameEntry::ValidateName(const FText& Text)
{
	if (Text.ToString().Len() >= 20)
		NameField->SetText(FText::FromString(Text.ToString().LeftChop(1)));
}

void UNameEntry::NativeConstruct()
{
	Super::NativeConstruct();

	ConfirmButton->OnClicked.AddUniqueDynamic(this, &UNameEntry::LoadGame);
	CancelButton->OnClicked.AddUniqueDynamic(this, &UNameEntry::Cancel);
	NameField->OnTextChanged.AddUniqueDynamic(this, &UNameEntry::ValidateName);
}
