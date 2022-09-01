// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interactable.h"
#include "MegajamCharacter.generated.h"


static int CollectedCrystalNum = 0;
static TArray<ACrystal*> CollectedCrystals = TArray<ACrystal*>();

UCLASS(config = Game)
class AMegajamCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

public:
	AMegajamCharacter();

	virtual void Tick(float DeltaTime) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, Category = Dash)
		float DashForce;

	UPROPERTY(EditAnywhere, Category = Dash)
		float DashCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grab)
		float GrabSocket;

	float DashStartTime;

	float IsDashed;

	AActor* GrabbedObject;

	AInteractable* InteractableObj;

	bool bInteractObject;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void Dash();

	void Grab();
	
	void GrabEnd();
	
	void AdjustDistanceGrabbedObject(float value);

	static void IncreaseCrystalNum(ACrystal* crystal) 
	{ 
		CollectedCrystalNum++; 
		CollectedCrystals.Add(crystal);
	};

	void InteractRaycast();

	void Interact();

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

