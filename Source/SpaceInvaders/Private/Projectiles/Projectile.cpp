// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders


#include "Projectiles/Projectile.h"

#include "AI/Alien.h"
#include "Player/ShipController.h"
#include "Player/ShipPlayer.h"


// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	SetRootComponent(Mesh);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Projectile(TEXT("/Game/SpaceInvaders/Art/3D/Rocket.Rocket"));
	Mesh->SetStaticMesh(Projectile.Object);

	Movement->InitialSpeed = Velocity;
	Movement->ProjectileGravityScale = 0;
	Mesh->SetCollisionProfileName("PlayerProjectile");

	Mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	InitialLifeSpan = 5;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::SetDirection(const FVector& Direction, float NewVelocity)
{
	Velocity = NewVelocity;
	Movement->Velocity = Direction * Velocity;
}

void AProjectile::SetDamageRange(const FVector2f& NewDamage)
{
	Damage = NewDamage;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
                        FVector NormalImpulse, const FHitResult& Hit)
{
	if (const AAlien* Alien = dynamic_cast<AAlien*>(OtherActor))
	{
		Alien->GetHealthModule()->DoDamage(FMath::RandRange(Damage.X, Damage.Y), GetOwner());
		Destroy();
	}
	else if (const AShipPlayer* Player = dynamic_cast<AShipPlayer*>(OtherActor))
	{
		static_cast<AShipController*>(Player->GetController())->GetHealthModule()->DoDamage(
			FMath::RandRange(Damage.X, Damage.Y), GetOwner());
		Destroy();
	}
	else if (OtherActor->IsA(AProjectile::StaticClass()))
	{
		Destroy();
		OtherActor->Destroy();
	}
}

UStaticMeshComponent* AProjectile::GetMesh() const
{
	return Mesh;
}
