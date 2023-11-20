// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ShipPlayer.h"

#include "Projectile.h"
#include "Player/ShipController.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PlayerState.h"
#include "UI/HUDManager.h"
#include "UI/PlayerHUD.h"

AShipPlayer::AShipPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	PlayerMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	PlayerMesh->SetCollisionProfileName("Player");
}

void AShipPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AShipPlayer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void AShipPlayer::MoveRight(const float Value)
{
	if (Controller == nullptr || Value == 0.0f)
		return;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // get right vector 
	AddMovementInput(Direction, Value); // add movement in that direction
}

void AShipPlayer::Fire()
{
	if (!CanFire) return;
	const auto Here = GetActorLocation();
	if (const auto Projectile = GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass(), Here,
	                                                                FRotator::ZeroRotator))
	{
		Projectile->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = -FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		Projectile->SetDirection(Direction);
		Projectile->SetOwner(this);
		Projectile->GetMesh()->SetCollisionProfileName("PlayerProjectile");
		CanFire = false;

		GetWorld()->GetTimerManager().SetTimer(
			FireDelayHandle,
			this,
			&AShipPlayer::ResetFire,
			FireDelay,
			false);
	}
}

void AShipPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShipPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShipPlayer::MoveRight);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShipPlayer::Fire);
}
