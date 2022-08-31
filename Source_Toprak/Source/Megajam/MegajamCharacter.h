// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MegajamCharacter.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float MaxHealth;

	float DashStartTime;

	float IsDashed;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void Dash();

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

