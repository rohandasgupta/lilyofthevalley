// Fill out your copyright notice in the Description page of Project Settings.


#include "PropaneTank.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APropaneTank::APropaneTank()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh 1"));
	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh 2"));
	Mesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh 3"));
	Mesh4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh 4"));

	Mesh2->SetupAttachment(Mesh1);
	Mesh3->SetupAttachment(Mesh1);
	Mesh4->SetupAttachment(Mesh1);

	customRender(false);

}

// Called when the game starts or when spawned
void APropaneTank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APropaneTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APropaneTank::customRender(bool b)
{
	Mesh1->SetRenderCustomDepth(b);
	Mesh2->SetRenderCustomDepth(b);
	Mesh3->SetRenderCustomDepth(b);
	Mesh4->SetRenderCustomDepth(b);
}