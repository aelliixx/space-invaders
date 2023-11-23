// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders


#include "Player/ShipPlayer.h"

#include "Blueprint/UserWidget.h"
#include "Projectiles/Projectile.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "Player/ShipController.h"
#include "UI/HUDManager.h"

AShipPlayer::AShipPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	PlayerMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	PlayerMesh->SetCollisionProfileName("Player");
	SetRootComponent(PlayerMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/SpaceInvaders/Art/3D/Ship"));
	if (Mesh.Succeeded())
		PlayerMesh->SetStaticMesh(Mesh.Object);

	static ConstructorHelpers::FClassFinder<UUserWidget> PauseMenu(TEXT("/Game/SpaceInvaders/UI/W_PauseMenu"));
	if (PauseMenu.Succeeded())
		PauseMenuClass = PauseMenu.Class;

	static ConstructorHelpers::FObjectFinder<USoundBase> PlayerFireObj(TEXT("/Game/SpaceInvaders/Audio/A_PlayerFire"));
	if (PlayerFireObj.Succeeded())
		FireSound = PlayerFireObj.Object;


	PlayerMovement->SetPlaneConstraintEnabled(true);
	PlayerMovement->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::X);
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

		if (FireSound)
			UGameplayStatics::PlaySound2D(GetWorld(), FireSound);

		CanFire = false;

		GetWorld()->GetTimerManager().SetTimer(
			FireDelayHandle,
			this,
			&AShipPlayer::ResetFire,
			FireDelay,
			false);
	}
}

void AShipPlayer::Pause()
{
	if (GetWorld()->GetName() == "MainMenu") return;
	const auto Controller = Cast<AShipController>(GetController());
	const auto IsPaused = Controller->IsPaused();
	Controller->SetPause(!IsPaused);
	Cast<AHUDManager>(Controller->GetHUD())->SetShowPauseMenu(!IsPaused);
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
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AShipPlayer::Pause).bExecuteWhenPaused = true;
}
