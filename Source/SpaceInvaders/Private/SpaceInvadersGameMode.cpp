// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders


#include "SpaceInvadersGameMode.h"

#include "SpaceInvadersGameState.h"
#include "Player/ShipController.h"
#include "Player/ShipPlayer.h"
#include "UI/HUDManager.h"


ASpaceInvadersGameMode::ASpaceInvadersGameMode()
{
	PlayerControllerClass = AShipController::StaticClass();
	DefaultPawnClass = AShipPlayer::StaticClass();
	HUDClass = AHUDManager::StaticClass();
	GameStateClass = ASpaceInvadersGameState::StaticClass();
}
