// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders


#include "SpaceInvadersGameInstance.h"

#include "Kismet/GameplayStatics.h"

void USpaceInvadersGameInstance::Init()
{
	Super::Init();
	LeaderboardSaveGame = Cast<ULeaderboardSaveGame>(UGameplayStatics::LoadGameFromSlot(LeaderboardSaveSlot, 0));
	if (LeaderboardSaveGame) return;
	LeaderboardSaveGame = Cast<ULeaderboardSaveGame>(
		UGameplayStatics::CreateSaveGameObject(ULeaderboardSaveGame::StaticClass()));

	UGameplayStatics::SaveGameToSlot(LeaderboardSaveGame, LeaderboardSaveSlot, 0);
}

void USpaceInvadersGameInstance::SaveLeaderboard(const FLeaderboard& ToSave)
{
	if (!LeaderboardSaveGame) return;
	LeaderboardSaveGame->Leaderboard = ToSave;
	UGameplayStatics::SaveGameToSlot(LeaderboardSaveGame, LeaderboardSaveSlot, 0);
}

TObjectPtr<ULeaderboardSaveGame> USpaceInvadersGameInstance::LoadLeaderboard() const
{
	return LeaderboardSaveGame;
}

void USpaceInvadersGameInstance::AddPlayerToLeaderboard(const int64 Score)
{
	if (const auto* Player = LeaderboardSaveGame->Leaderboard.Map.Find(PlayerName);
		Player && *Player > Score)
		return;
	LeaderboardSaveGame->Leaderboard.Map.Add(PlayerName, Score);
	SaveLeaderboard(LeaderboardSaveGame->Leaderboard);
}

void USpaceInvadersGameInstance::SetPlayerName(const FName& Name)
{
	PlayerName = Name;
}

FName USpaceInvadersGameInstance::GetPlayerName() const
{
	return PlayerName;
}
