// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Leaderboard/Leaderboard.h"
#include "LeaderboardSaveGame.generated.h"

/**
 * 
 */



UCLASS()
class SPACEINVADERS_API ULeaderboardSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FLeaderboard Leaderboard;
};
