// Fill out your copyright notice in the Description page of Project Settings.


#include "MustafaGulsoy/Trigger/TriggerOfTempleGates.h"



// <==========================================================================================================================================================>


// include draw debug helpers header file
#include "DrawDebugHelpers.h"

ATriggerOfTempleGates::ATriggerOfTempleGates()
{
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void ATriggerOfTempleGates::BeginPlay()
{
	Super::BeginPlay();
	DrawDebugBox(GetWorld(), GetActorLocation(), GetActorScale() * 100, FColor::Cyan, true, -1, 0, 5);

	OnActorBeginOverlap.AddDynamic(this, &ATriggerOfTempleGates::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ATriggerOfTempleGates::OnOverlapEnd);




}


void ATriggerOfTempleGates::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor)
	{
		if (OtherActor != this)
			isInTrigger = true;
	}
	UE_LOG(LogTemp, Display, TEXT("hASDASD"));



}

void ATriggerOfTempleGates::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{

	if (OtherActor)
	{
		if (OtherActor != this)
			isInTrigger = false;
	}
	UE_LOG(LogTemp, Display, TEXT("hASDASD"));
}


void ATriggerOfTempleGates::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	gateLocation = gate->GetActorLocation();

	buttomLocation = button->GetActorLocation();


	if (isInTrigger)

	{
		gate->SetActorLocation(gate->GetActorLocation() + speedVector * DeltaTime);
		button->SetActorLocation(button->GetActorLocation() + speedVector * DeltaTime);
	}
	else
	{
		gate->SetActorLocation(gate->GetActorLocation() - speedVector * DeltaTime);
		button->SetActorLocation(button->GetActorLocation() - speedVector * DeltaTime);
	}


	if (gate->GetActorLocation().X > gateTopLimit.X)
	{
		gate->SetActorLocation(FVector(gateTopLimit.X, gateLocation.Y, gateLocation.Z));
	}
	if (gate->GetActorLocation().Y > gateTopLimit.Y)
	{
		gate->SetActorLocation(FVector(gateLocation.X, gateTopLimit.Y, gateLocation.Z));
	}
	if (gate->GetActorLocation().Z > gateTopLimit.Z)
	{
		gate->SetActorLocation(FVector(gateLocation.X, gateLocation.Y, gateTopLimit.Z));
	}


	if (button->GetActorLocation().X > buttonTopLimit.X)
	{
		button->SetActorLocation(FVector(buttonTopLimit.X, gateLocation.Y, gateLocation.Z));
	}

	if (button->GetActorLocation().Y > buttonTopLimit.Y)
	{
		button->SetActorLocation(FVector(gateLocation.X, buttonTopLimit.Y, gateLocation.Z));
	}
	if (button->GetActorLocation().Z > buttonTopLimit.Z)
	{
		button->SetActorLocation(FVector(gateLocation.X, gateLocation.Y, buttonTopLimit.Z));
	}

	// <==================================================================> \\

	if (gate->GetActorLocation().X < gateBottomLimit.X)
	{
		gate->SetActorLocation(FVector(gateBottomLimit.X, gateLocation.Y, gateLocation.Z));
	}

	if (gate->GetActorLocation().Y < gateBottomLimit.Y)
	{
		gate->SetActorLocation(FVector(gateLocation.X, gateBottomLimit.Y, gateLocation.Z));
	}
	if (gate->GetActorLocation().Z < gateBottomLimit.Z)
	{
		gate->SetActorLocation(FVector(gateLocation.X, gateLocation.Y, gateBottomLimit.Z));
	}

	if (button->GetActorLocation().X < buttonBottomLimit.X)
	{
		button->SetActorLocation(FVector(buttonBottomLimit.X, gateLocation.Y, gateLocation.Z));
	}

	if (button->GetActorLocation().Y < buttonBottomLimit.Y)
	{
		button->SetActorLocation(FVector(gateLocation.X, buttonBottomLimit.Y, gateLocation.Z));
	}
	if (button->GetActorLocation().Z < buttonBottomLimit.Z)
	{
		button->SetActorLocation(FVector(gateLocation.X, gateLocation.Y, buttonBottomLimit.Z));
	}


}

