// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthBar.h"

#include "Components/ProgressBar.h"
#include "UI/HUDManager.h"


void UHealthBar::Update()
{
	const auto HUD = Cast<AHUDManager>(GetOwningPlayer()->GetHUD());
	Bar->SetPercent(HUD->GetPlayerHP() / HUD->GetPlayerMaxHP());
}
