// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireballActor.h"
#include "GameFramework/Actor.h"
#include "Iceball.generated.h"

/**
 *
 */
UCLASS()
class MEGAJAM_API AIceball : public AFireballActor
{
	GENERATED_BODY()

public:

	AIceball();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
