// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders


#include "UI/HUDManager.h"

#include "Blueprint/UserWidget.h"
#include "Player/ShipController.h"
#include "UI/MainMenu.h"
#include "UI/PlayerHUD.h"


AHUDManager::AHUDManager() : HUD(nullptr)
{
	PrimaryActorTick.TickInterval = 0.1f;
	static ConstructorHelpers::FClassFinder<UPlayerHUD> HudWidget(TEXT("/Game/SpaceInvaders/UI/W_PlayerHUD"));
	static ConstructorHelpers::FClassFinder<UDeathScreen> DeathScreenWidget(TEXT("/Game/SpaceInvaders/UI/W_DeathScreen"));
	static ConstructorHelpers::FClassFinder<UMainMenu> MainMenuWidget(TEXT("/Game/SpaceInvaders/UI/W_MainMenu"));
	static ConstructorHelpers::FClassFinder<UPauseMenu> PauseMenuWidget(TEXT("/Game/SpaceInvaders/UI/W_PauseMenu"));

	PlayerHudClass = HudWidget.Class;
	DeathScreenClass = DeathScreenWidget.Class;
	MainMenuClass = MainMenuWidget.Class;
	PauseMenuClass = PauseMenuWidget.Class;
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

	Controller->ShowMouseCursor(false);
	SetShowHUD(true);
}

TObjectPtr<UDeathScreen> AHUDManager::GetDeathScreen() const
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
		SetShowHUD(false);
		return;
	}
	if (PauseMenu)
		PauseMenu->RemoveFromParent();
	Controller->ShowMouseCursor(false);
	SetShowHUD(true);
	PauseMenu = nullptr;
}
