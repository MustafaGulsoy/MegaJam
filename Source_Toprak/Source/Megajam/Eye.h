// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Eye.generated.h"

UCLASS()
class MEGAJAM_API AEye : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEye();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	USpringArmComponent* Socket;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	USpringArmComponent* GetSocket();

	bool IsSocketFilled;

};
