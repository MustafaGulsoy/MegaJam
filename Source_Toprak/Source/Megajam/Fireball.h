// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireballActor.h"
#include "Fireball.generated.h"

/**
 * 
 */
UCLASS()
class MEGAJAM_API AFireball : public AFireballActor
{
	GENERATED_BODY()

	AFireball();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
