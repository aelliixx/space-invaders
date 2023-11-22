// Fill out your copyright notice in the Description page of Project Settings.


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
