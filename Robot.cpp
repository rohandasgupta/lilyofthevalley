// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARobot::ARobot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARobot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bWalking) {
		AddMovementInput(GetActorForwardVector());
	}
	
}

// Called to bind functionality to input
void ARobot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARobot::customRender(bool b)
{
	GetMesh()->SetRenderCustomDepth(b);
}

