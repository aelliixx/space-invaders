// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

#pragma once

#include "CoreMinimal.h"
#include "Player/ShipPlayer.h"
#include "Projectiles/Projectile.h"
#include "Powerup.generated.h"


UCLASS(Abstract)
class SPACEINVADERS_API APowerup : public AProjectile
{
	GENERATED_BODY()

public:
	APowerup();

protected:
	virtual void BeginPlay() override;

	virtual void ApplyPowerup(AShipPlayer* Actor) PURE_VIRTUAL(APowerup::ApplyPowerup,);
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
						FVector NormalImpulse, const FHitResult& Hit) override;

public:
	virtual void Tick(float DeltaTime) override;
};
