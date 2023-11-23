// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

#pragma once

#include "CoreMinimal.h"
#include "LeaderboardSaveGame.h"
#include "Engine/GameInstance.h"
#include "SpaceInvadersGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERS_API USpaceInvadersGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;

	FString LeaderboardSaveSlot = "Leaderboard";

	UPROPERTY()
	TObjectPtr<ULeaderboardSaveGame> LeaderboardSaveGame;

	FName PlayerName;

public:
	void SaveLeaderboard(const FLeaderboard&);
	TObjectPtr<ULeaderboardSaveGame> LoadLeaderboard() const;
	void AddPlayerToLeaderboard(const int64);

	void SetPlayerName(const FName&);
	FName GetPlayerName() const;
};
