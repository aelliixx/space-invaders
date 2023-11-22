// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Alien.h"

#include "Projectiles/Projectile.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Player/ShipController.h"
#include "Player/ShipPlayer.h"
#include "Projectiles/Powerups/HealthPowerup.h"


// Sets default values
AAlien::AAlien()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Alien1(TEXT("/Game/SpaceInvaders/Art/3D/Alien1.Alien1"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Alien2(TEXT("/Game/SpaceInvaders/Art/3D/Alien2.Alien2"));
	NormalMesh = Alien1.Object;
	AlternateMesh = Alien2.Object;
	Mesh->SetStaticMesh(NormalMesh);
	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> RocketMaterialInstance(
		TEXT("/Game/SpaceInvaders/Art/Materials/MI_Red.MI_Red"));
	RocketMaterial = RocketMaterialInstance.Object;


	Health = CreateDefaultSubobject<UHealthModule>(TEXT("Health"));
	Mesh->SetCollisionProfileName("Enemy");

	Health->SetMaxHP(1);
}

void AAlien::Fire()
{
	const auto Here = GetActorLocation();
	if (const auto Projectile = GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass(), Here,
	                                                                FRotator::ZeroRotator))
	{
		Projectile->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		const FRotator YawRotation(0, GetActorRotation().Yaw, 0);
		const FVector Direction = -FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		Projectile->SetDirection(Direction);
		Projectile->SetOwner(this);
		Projectile->GetMesh()->SetCollisionProfileName("EnemyProjectile");
		Projectile->GetMesh()->SetMaterial(0, RocketMaterial);
	}
}

void AAlien::SwapMesh()
{
	Mesh->SetStaticMesh(CurrentMeshIndex == 0 ? AlternateMesh : NormalMesh);
	CurrentMeshIndex = !CurrentMeshIndex;
}

// Called when the game starts or when spawned
void AAlien::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		FireHandle,
		this,
		&AAlien::Fire,
		FMath::RandRange(FireInterval.X, FireInterval.Y),
		true);

	Health->FOnDeathDelegate.AddLambda([this](AActor* It, AActor* Source)
	{
		if (It == this && Source)
		{
			const auto Player = Cast<AShipPlayer>(Source);
			Cast<AShipController>(Player->GetController())->GetScoreModule()->AddScore(PointWorth);
			Destroy();
		}
	});
}

void AAlien::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (FMath::FRand() <= ChanceToDropPowerup)
	{
		if (const auto Powerup = GetWorld()->SpawnActor<AHealthPowerup>(AHealthPowerup::StaticClass(), GetActorLocation(),
		                                                          FRotator::ZeroRotator))
		{
			const FRotator YawRotation(0, GetActorRotation().Yaw, 0);
			const FVector Direction = -FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			Powerup->SetDirection(Direction, 100);
		}
	}
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AAlien::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UHealthModule* AAlien::GetHealthModule() const
{
	return Health;
}

int64 AAlien::GetPointWorth() const
{
	return PointWorth;
}
