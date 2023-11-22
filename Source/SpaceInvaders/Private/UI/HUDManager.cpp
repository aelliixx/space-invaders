// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDManager.h"

#include "Blueprint/UserWidget.h"
#include "Player/ShipController.h"
#include "UI/MainMenu.h"
#include "UI/PlayerHUD.h"


AHUDManager::AHUDManager() : HUD(nullptr)
{
	PrimaryActorTick.TickInterval = 0.1f;
	static ConstructorHelpers::FClassFinder<UPlayerHUD> Hud(TEXT("/Game/SpaceInvaders/UI/W_PlayerHUD"));
	static ConstructorHelpers::FClassFinder<UDeathScreen> DeathScreen(TEXT("/Game/SpaceInvaders/UI/W_DeathScreen"));
	static ConstructorHelpers::FClassFinder<UMainMenu> MainMenu(TEXT("/Game/SpaceInvaders/UI/W_MainMenu"));
	static ConstructorHelpers::FClassFinder<UPauseMenu> PauseMenu(TEXT("/Game/SpaceInvaders/UI/W_PauseMenu"));

	PlayerHudClass = Hud.Class;
	DeathScreenClass = DeathScreen.Class;
	MainMenuClass = MainMenu.Class;
	PauseMenuClass = PauseMenu.Class;
}

void AHUDManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (HUD)
		HUD->Update();
}

void AHUDManager::BeginPlay()
{
	Super::BeginPlay();
	AShipController* Controller = Cast<AShipController>(GetOwner());
	if (GetWorld()->GetName() == "MainMenu")
	{
		const auto MainMenuWidget = CreateWidget(Controller, MainMenuClass);
		MainMenuWidget->AddToViewport();
		Controller->ShowMouseCursor(true);
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		GetOwningPlayerController()->SetInputMode(InputMode);
		return;
	}

	Controller->OnHealthChangedDelegate.AddUObject(
		this, &AHUDManager::SetPlayerHP);
	Controller->OnScoreChangedDelegate.AddUObject(
		this, &AHUDManager::SetPlayerScore);

	PlayerMaxHP = Controller->GetHealthModule()->GetMaxHP();
	PlayerHP = Controller->GetHealthModule()->GetCurrentHealth();
	Controller->ShowMouseCursor(false);
	SetShowHUD(true);
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

UDeathScreen* AHUDManager::GetDeathScreen() const
{
	return DeathScreen;
}

void AHUDManager::SetShowHUD(const bool Show)
{
	if (Show)
	{
		HUD = CreateWidget<UPlayerHUD>(GetOwningPlayerController(), PlayerHudClass);
		if (HUD)
			HUD->AddToViewport(1);
		return;
	}
	if (HUD)
		HUD->RemoveFromParent();
	HUD = nullptr;
}

void AHUDManager::SetShowDeathScreen(const bool Show)
{
	AShipController* Controller = Cast<AShipController>(GetOwner());
	if (Show)
	{
		DeathScreen = CreateWidget<UDeathScreen>(Controller, DeathScreenClass);
		if (DeathScreen)
			DeathScreen->AddToViewport(2);
		Controller->ShowMouseCursor(true);
		return;
	}
	if (DeathScreen)
		DeathScreen->RemoveFromParent();
	Controller->ShowMouseCursor(false);
	DeathScreen = nullptr;
}

void AHUDManager::SetShowPauseMenu(const bool Show)
{
	AShipController* Controller = Cast<AShipController>(GetOwner());
	if (Show)
	{
		PauseMenu = CreateWidget<UPauseMenu>(GetWorld(), PauseMenuClass);
		if (PauseMenu)
			PauseMenu->AddToViewport();
		PauseMenu->SetScore(Controller->GetScoreModule()->GetScore());
		Controller->ShowMouseCursor(true);
		return;
	}
	if (PauseMenu)
		PauseMenu->RemoveFromParent();
	Controller->ShowMouseCursor(false);
	PauseMenu = nullptr;
}
