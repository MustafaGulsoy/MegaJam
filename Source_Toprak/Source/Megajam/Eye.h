// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireballActor.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Eye.generated.h"

UCLASS()
class MEGAJAM_API AEye : public AActor
{
	GENERATED_BODY()

public:
	AEye();

protected:
	virtual void BeginPlay() override;

	USpringArmComponent* Socket;

	AFireballActor* Ball;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Fireball)
		TEnumAsByte<BallType> BallType;

	USpringArmComponent* GetSocket();

	bool IsSocketFilled;

	AFireballActor* GetBall();

	void SetBall(AFireballActor* ball);

};
