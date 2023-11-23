// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class SPACEINVADERS_API AProjectile : public AActor
{
	GENERATED_BODY()

protected:
	AProjectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* Movement;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Projectile)
	float Velocity = 500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Projectile)
	FVector2f Damage = {5, 20}; // Min-max damage


public:
	virtual void Tick(float DeltaTime) override;
	void SetDirection(const FVector& Direction, float NewVelocity = 500);
	void SetDamageRange(const FVector2f& NewDamage);

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	           FVector NormalImpulse, const FHitResult& Hit);

	UStaticMeshComponent* GetMesh() const;
};
