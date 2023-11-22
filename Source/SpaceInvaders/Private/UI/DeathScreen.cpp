// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DeathScreen.h"

#include "Kismet/GameplayStatics.h"
#include "Player/ShipController.h"

void UDeathScreen::OnRestart()
{
	GEngine->AddOnScreenDebugMessage(static_cast<uint64>(-1), 5, FColor::Orange, TEXT("Restart!"));
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
