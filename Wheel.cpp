// Fill out your copyright notice in the Description page of Project Settings.


#include "Wheel.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AWheel::AWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel"));
}

// Called when the game starts or when spawned
void AWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (water)
	{
		Mesh->SetRelativeRotation(Mesh->GetRelativeRotation() + FRotator(0.f, 0.f, -DeltaTime * speed));
	}

	else
	{
		Mesh->SetRelativeRotation(Mesh->GetRelativeRotation() + FRotator(-DeltaTime * speed,0.f, 0.f ));
	}
}

