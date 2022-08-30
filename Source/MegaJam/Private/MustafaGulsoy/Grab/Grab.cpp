// Fill out your copyright notice in the Description page of Project Settings.


#include "MustafaGulsoy/Grab/Grab.h"

// Sets default values for this component's properties
UGrab::UGrab()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	// ...
}


// Called when the game starts
void UGrab::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UGrab::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	// ...
}


void UGrab::GrabItem() {

	//UE_LOG(LogTemp, Display, TEXT("Anything can happen"));

	//if (grabbedObject == nullptr)
	//{
	//	FHitResult hit;
	//	FVector ForwardVector = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector();
	//	FVector start = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetTransform().GetLocation() + FVector(0, 0, 80); ;
	//	FVector end = ((ForwardVector * 1000.f) + start);

	//	DrawDebugLine(GetWorld(), start, end, FColor::Green, false, 1, 0, 1);
	//	FCollisionQueryParams collisionParams;

	//	isHit = GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, collisionParams);

	//	if (isHit)

	//	{
	//		if (hit.GetActor() != GetOwner())
	//		{
	//			grabbedObject = hit.GetActor();
	//			UE_LOG(LogTemp, Display, TEXT("%s"), *grabbedObject->GetName());
	//			grabbedObject->SetActorLocation(FVector(1, 2, 3));
	//			UE_LOG(LogTemp, Display, TEXT("Aldi"));

	//		}
	//	}
	//}


}


void UGrab::ReleaseItem()
{
	//grabbedObject = nullptr;
	//UE_LOG(LogTemp, Display, TEXT("Birakti"));

}

