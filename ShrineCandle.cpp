// Fill out your copyright notice in the Description page of Project Settings.


#include "ShrineCandle.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AShrineCandle::AShrineCandle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Msh"));

	lanternSpawn = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("lanternSpawn"));
}

// Called when the game starts or when spawned
void AShrineCandle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShrineCandle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShrineCandle::customRender(bool b)
{
	Mesh->SetRenderCustomDepth(b);
}