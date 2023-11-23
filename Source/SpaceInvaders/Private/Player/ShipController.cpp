// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders


#include "Player/ShipController.h"

#include "SpaceInvadersGameInstance.h"
#include "SpaceInvadersGameState.h"
#include "UI/HUDManager.h"


void AShipController::OnDeath(AActor* It, AActor*)
{
	if (It == this && !IsDead)
	{
		Cast<USpaceInvadersGameInstance>(GetGameInstance())->AddPlayerToLeaderboard(Score->GetScore());
		const auto HUDManager = Cast<AHUDManager>(GetHUD());
		HUDManager->SetShowHUD(false);
		HUDManager->SetShowDeathScreen(true);
		GetPawn()->Destroy();
		IsDead = true;
	}
}

void AShipController::OnLowerBoundReached()
{
	OnDeath(this, nullptr);
}

AShipController::AShipController()
{
	Health = CreateDefaultSubobject<UHealthModule>(TEXT("Health"));
	Score = CreateDefaultSubobject<UScoreModule>(TEXT("Score"));
}

void AShipController::BeginPlay()
{
	Super::BeginPlay();
	
	Health->FOnDeathDelegate.AddUObject(this, &AShipController::OnDeath);
	Cast<ASpaceInvadersGameState>(GetWorld()->GetGameState())
		->OnLowerBoundReachedDelegate.AddUObject(this, &AShipController::OnLowerBoundReached);
}

UHealthModule* AShipController::GetHealthModule() const
{
	return Health;
}

UScoreModule* AShipController::GetScoreModule() const
{
	return Score;
}

void AShipController::SetPlayerName(const FName Name)
{
	PlayerName = Name;
}

FName AShipController::GetPlayerName() const
{
	return PlayerName;
}

void AShipController::ShowMouseCursor(const bool Show)
{
	SetShowMouseCursor(Show);
	if (Show)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetHideCursorDuringCapture(false);
		SetInputMode(InputMode);
	}
	else
		SetInputMode(FInputModeGameOnly());
}
