// Fill out your copyright notice in the Description page of Project Settings.

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

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	
	float PlayerHP{};
	float PlayerMaxHP{};
	int64 Score{};

	void SetPlayerHP(const float);
	void SetPlayerMaxHP(const float);
	void SetPlayerScore(const int64);
public:

	float GetPlayerHP() const;
	float GetPlayerMaxHP() const;
	int64 GetPlayerScore() const;

	UDeathScreen* GetDeathScreen() const;

	void SetShowHUD(const bool);
	void SetShowDeathScreen(const bool);
	void SetShowPauseMenu(const bool);
	

};
