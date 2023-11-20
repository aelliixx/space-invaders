// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreText.h"
#include "Components/TextBlock.h"
#include "UI/HUDManager.h"


void UScoreText::Update()
{
	const auto Score = Cast<AHUDManager>(GetOwningPlayer()->GetHUD())->GetPlayerScore();
	ScoreText->SetText(FText::Format(FTextFormat::FromString(TEXT("Score: {0}")), Score));
}

