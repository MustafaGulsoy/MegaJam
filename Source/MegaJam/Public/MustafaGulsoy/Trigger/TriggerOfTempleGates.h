

#pragma once
#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "TriggerOfTempleGates.generated.h"

/**
 *
 */
UCLASS()
class  ATriggerOfTempleGates : public ATriggerVolume
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* button = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* gate = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gate")
		FVector gateBottomLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gate")
		FVector gateTopLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
		FVector buttonBottomLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
		FVector buttonTopLimit;

	//< ===========================================================================>  \\
	
	bool isInTrigger = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger/ButtonSpeed")
		FVector gateSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger/ButtonSpeed")
		FVector buttonSpeed;

	UPROPERTY()
		FVector buttomLocation;

	UPROPERTY()
		FVector gateLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// constructor sets default values for this actor's properties
	ATriggerOfTempleGates();

	virtual void Tick(float DeltaTime) override;

	// overlap begin function
	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	// overlap end function
	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);




};
