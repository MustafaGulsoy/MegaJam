// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Eye.h"
#include "FireballActor.generated.h"

UCLASS()
class MEGAJAM_API AFireballActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFireballActor();

protected:
	// Called when the game starts or when spawnedS
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Fireball)
		UNiagaraSystem* NS_Fireball;

	UPROPERTY(EditAnywhere, Category = Fireball)
		USoundBase* SB_Fireball;

	UPROPERTY(EditAnywhere, Category = Fireball)
		float FireballRange;

	UPROPERTY(EditAnywhere, Category = Fireball)
		float FireballSpeedFire;

	USpringArmComponent* DefaultSocket;

	USpringArmComponent* CurrentSocket;

	void Fire();

	void RaycastFromCamera();

	void HitTheGround();

	bool ShouldComeBack();

	FVector TargetLoc;

	int Direction = 1;

	bool IsAttacking;

	bool IsMovingToSocketComplete;

	UStaticMeshComponent* MeshSphere;

	AEye* AttachedEye;
};
