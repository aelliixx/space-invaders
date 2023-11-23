// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

#pragma once
#include "CoreMinimal.h"
#include "Leaderboard.generated.h"

/**
 * 
 */
USTRUCT()
struct FLeaderboard
{
	GENERATED_BODY()
	// PlayerName, Score
	UPROPERTY()
	TMap<FName, int64> Map;
};