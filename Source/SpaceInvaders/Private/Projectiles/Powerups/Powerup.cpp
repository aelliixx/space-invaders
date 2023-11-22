// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/Powerups/Powerup.h"

#include "AI/Alien.h"

APowerup::APowerup()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APowerup::BeginPlay()
{
	Super::BeginPlay();
}

void APowerup::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
						FVector NormalImpulse, const FHitResult& Hit)
{
	if (const auto Player = dynamic_cast<AShipPlayer*>(OtherActor))
	{
		ApplyPowerup(Player);
		Destroy();
	}
	if (OtherActor->IsBasedOnArchetype(AAlien::StaticClass()))
	{
		Destroy();
	}
}

void APowerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
