// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders


#include "UI/DeathScreen.h"

#include "Kismet/GameplayStatics.h"
#include "Player/ShipController.h"

void UDeathScreen::OnRestart()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void UDeathScreen::OnExitToMainMenu()
{
	UGameplayStatics::OpenLevel(this, FName("MainMenu"), false);
}

void UDeathScreen::SetScore(const int64 Score) const
{
	ScoreText->SetText(FText::Format(
		FText::FromString("Score: {0}"),
		FText::FromString(FString::FromInt(Score))));
}

void UDeathScreen::NativeConstruct()
{
	Super::NativeConstruct();
	Restart->OnClicked.AddUniqueDynamic(this, &UDeathScreen::OnRestart);
	MainMenu->OnClicked.AddUniqueDynamic(this, &UDeathScreen::OnExitToMainMenu);
	SetScore(Cast<AShipController>(GetOwningPlayer())->GetScoreModule()->GetScore());
}
