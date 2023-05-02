// Fill out your copyright notice in the Description page of Project Settings.

#include "TestProject/TestProject.h"
#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCameraDirector::UCameraDirector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraDirector::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCameraDirector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	const float TimeBetweenCameraChanges = 2.0f;
	const float SmoothBlendTime = 0.75f;
	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		// Find the actor that handles control for the local player.
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurPlayerController)
		{
			if (CameraTwo && (OurPlayerController->GetViewTarget() == CameraOne))
			{
				// Blend smoothly to camera two.
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			}
			else if (CameraOne)
			{
				// Cut instantly to camera one.
				OurPlayerController->SetViewTarget(CameraOne);
			}
		}
	}
	// ...
}

