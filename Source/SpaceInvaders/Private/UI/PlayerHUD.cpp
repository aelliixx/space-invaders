// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerHUD::Update()
{
	if (HealthBar)
		HealthBar->Update();
	if (ScoreText)
		ScoreText->Update();
}
