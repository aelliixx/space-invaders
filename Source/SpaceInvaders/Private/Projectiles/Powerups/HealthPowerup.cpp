// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/Powerups/HealthPowerup.h"

#include "AI/Alien.h"
#include "Player/ShipController.h"
#include "Player/ShipPlayer.h"
#include "Projectiles/Projectile.h"


void AHealthPowerup::ApplyPowerup(AShipPlayer* Player)
{
	Cast<AShipController>(Player->GetController())->GetHealthModule()->DoDamage(-HealthAmount);
}



AHealthPowerup::AHealthPowerup()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Projectile(TEXT("/Game/SpaceInvaders/Art/3D/Heart.Heart"));
	Mesh->SetStaticMesh(Projectile.Object);
	Mesh->SetCollisionProfileName("EnemyProjectile");
	InitialLifeSpan = 30;
}

void AHealthPowerup::SetHealthAmount(const float Amount)
{
	HealthAmount = Amount;
}

void AHealthPowerup::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHealthPowerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

