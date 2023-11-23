// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/Powerups/Powerup.h"
#include "HealthPowerup.generated.h"

UCLASS()
class SPACEINVADERS_API AHealthPowerup final : public APowerup
{
	GENERATED_BODY()

	float HealthAmount = 5;

	virtual void ApplyPowerup(AShipPlayer* Player) override;

public:
	// Sets default values for this actor's properties
	AHealthPowerup();

	void SetHealthAmount(float);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
