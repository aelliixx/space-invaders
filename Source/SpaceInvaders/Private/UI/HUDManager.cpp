// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDManager.h"

#include "Blueprint/UserWidget.h"
#include "Player/ShipController.h"
#include "UI/PlayerHUD.h"


AHUDManager::AHUDManager() : HUD(nullptr)
{
	PrimaryActorTick.TickInterval = 0.1f;
	static ConstructorHelpers::FClassFinder<UPlayerHUD> HudClass(TEXT("/Game/SpaceInvaders/UI/PlayerHUD"));
	PlayerHudClass = HudClass.Class;
}

void AHUDManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	HUD->Update();
}

void AHUDManager::BeginPlay()
{
	Super::BeginPlay();

	AShipController* Controller = Cast<AShipController>(GetOwner());
	Controller->OnHealthChangedDelegate.AddUObject(
		this, &AHUDManager::SetPlayerHP);
	Controller->OnScoreChangedDelegate.AddUObject(
		this, &AHUDManager::SetPlayerScore);

	PlayerMaxHP = Controller->GetHealthModule()->GetMaxHP();
	PlayerHP = Controller->GetHealthModule()->GetCurrentHealth();

	HUD = CreateWidget<UPlayerHUD>(Controller, PlayerHudClass);
	if (HUD)
		HUD->AddToViewport(1);
}

void AHUDManager::SetPlayerHP(const float Value)
{
	PlayerHP = Value;
}

void AHUDManager::SetPlayerMaxHP(const float Value)
{
	PlayerMaxHP = Value;
}

void AHUDManager::SetPlayerScore(const int64 Value)
{
	Score = Value;
}

float AHUDManager::GetPlayerHP() const
{
	return PlayerHP;
}

float AHUDManager::GetPlayerMaxHP() const
{
	return PlayerMaxHP;
}

int64 AHUDManager::GetPlayerScore() const
{
	return Score;
}
