// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

#pragma once

#include "CoreMinimal.h"
#include "DeathScreen.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "PlayerHUD.h"
#include "GameFramework/HUD.h"
#include "HUDManager.generated.h"


UCLASS()
class SPACEINVADERS_API AHUDManager : public AHUD
{
	GENERATED_BODY()

	AHUDManager();

	UPROPERTY()
	TObjectPtr<UPlayerHUD> HUD;
	UPROPERTY()
	TObjectPtr<UDeathScreen> DeathScreen;
	UPROPERTY()
	TObjectPtr<UPauseMenu> PauseMenu;

	TSubclassOf<UPlayerHUD> PlayerHudClass;
	TSubclassOf<UDeathScreen> DeathScreenClass;
	TSubclassOf<UMainMenu> MainMenuClass;
	TSubclassOf<UPauseMenu> PauseMenuClass;

	virtual void BeginPlay() override;
	
public:

	TObjectPtr<UDeathScreen> GetDeathScreen() const;

	void SetShowHUD(const bool);
	void SetShowDeathScreen(const bool);
	void SetShowPauseMenu(const bool);
	

};
