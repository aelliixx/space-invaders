// Fill out your copyright notice in the Description page of Project Settings.

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
	void SetDirection(const FVector& Direction);
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	           FVector NormalImpulse, const FHitResult& Hit);

	UStaticMeshComponent* GetMesh() const;
};
