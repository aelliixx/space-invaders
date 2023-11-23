// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

#pragma once

#include "CoreMinimal.h"
#include "Modules/HealthModule.h"
#include "GameFramework/Actor.h"
#include "Alien.generated.h"

UCLASS()
class SPACEINVADERS_API AAlien : public AActor
{
	GENERATED_BODY()

	FTimerHandle FireHandle;

	UPROPERTY()
	UMaterialInterface* RocketMaterial;

	
	void Fire();

	uint8 CurrentMeshIndex;

protected:
	UPROPERTY()
	TObjectPtr<UStaticMesh> NormalMesh;
	UPROPERTY()
	TObjectPtr<UStaticMesh> AlternateMesh;
	
	UPROPERTY()
	UHealthModule* Health;


	UPROPERTY()
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category=Score)
	int64 PointWorth = 10; // How many points is killing this alien worth

	UPROPERTY(EditAnywhere, Category=Stats)
	FVector2f FireInterval = {10, 20}; // How often the alien fires its weapons

	UPROPERTY(EditDefaultsOnly, Category=Stats)
	float ChanceToDropPowerup = 0.05f;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type) override;
	virtual void OnDeath(AActor* Source);

public:
	AAlien();
	virtual void Tick(float DeltaTime) override;

	UHealthModule* GetHealthModule() const;
	int64 GetPointWorth() const;
	void SwapMesh();
};
