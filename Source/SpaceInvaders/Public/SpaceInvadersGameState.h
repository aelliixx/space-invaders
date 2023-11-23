// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

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
