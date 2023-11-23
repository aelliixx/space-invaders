// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders


#include "UI/PauseMenu.h"

#include "Kismet/GameplayStatics.h"
#include "Player/ShipController.h"
#include "UI/HUDManager.h"

void UPauseMenu::OnResumeClicked()
{
	GetOwningPlayer()->SetPause(false);
	const auto HUDManager = Cast<AHUDManager>(GetOwningPlayer()->GetHUD());
	HUDManager->SetShowHUD(true);
	HUDManager->SetShowPauseMenu(false);
}

void UPauseMenu::OnQuitClicked()
{
	RemoveFromParent();
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu::OnResumeClicked);
	QuitButton->OnClicked.AddDynamic(this, &UPauseMenu::OnQuitClicked);
}

void UPauseMenu::SetScore(const int64 Score)
{
	ScoreText->SetText(
		FText::Format(FText::FromString("Score: {0}"),
		              FText::FromString(FString::FromInt(Score))
		)
	);
}
