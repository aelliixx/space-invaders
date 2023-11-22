// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenu.h"

#include "Kismet/GameplayStatics.h"
#include "Player/ShipController.h"

void UPauseMenu::OnResumeClicked()
{
	GetOwningPlayer()->SetPause(false);
	Cast<AShipController>(GetOwningPlayer())->ShowMouseCursor(false);
	RemoveFromParent();
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
