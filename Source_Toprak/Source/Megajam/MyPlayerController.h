// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MegajamCharacter.h"
#include "FireballActor.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.generated.h"

UCLASS()
class MEGAJAM_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

	AFireballActor* FireballActor;
	AFireballActor* IceballActor;

	AMegajamCharacter* possessedPawn;

private:
	void CallMoveForward(float value);
	void CallMoveRight(float value);
	void CallJump();
	void CallStopJumping();
	void CallAddControllerYawInput(float rate);
	void CallAddControllerPitchInput(float rate);
	void CallFireballFire();
	void CallIceballFire();
	void CallDash();
	void CallHitTheGround();
};
