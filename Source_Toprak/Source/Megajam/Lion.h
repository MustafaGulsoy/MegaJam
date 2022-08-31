// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.h"
#include "Lion.generated.h"

UCLASS()
class MEGAJAM_API ALion : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		USoundBase* FireSound;

	UPROPERTY(EditAnywhere, Category = Projectile)
		float RaycastRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	float ProjectileFireTimer;

	void RaycastToFindPlayer();

	void Fire();
};
