// Fill out your copyright notice in the Description page of Project Settings.


#include "CampfireBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACampfireBase::ACampfireBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock"));
}

// Called when the game starts or when spawned
void ACampfireBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACampfireBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACampfireBase::customRender(bool b)
{
	RockMesh->SetRenderCustomDepth(b);
}