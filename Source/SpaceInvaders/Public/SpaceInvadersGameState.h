// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SpaceInvadersGameState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnLowerBoundReachedSignature)


/**
 * 
 */
UCLASS()
class SPACEINVADERS_API ASpaceInvadersGameState : public AGameStateBase
{
	GENERATED_BODY()


public:
	FOnLowerBoundReachedSignature OnLowerBoundReachedDelegate;
};
