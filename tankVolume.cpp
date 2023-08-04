// Fill out your copyright notice in the Description page of Project Settings.


#include "tankVolume.h"
#include "Components/BoxComponent.h"
#include "PropaneTank.h"

// Sets default values
AtankVolume::AtankVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	vol = CreateDefaultSubobject<UBoxComponent>(TEXT("Volume"));

	vol->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void AtankVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AtankVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<AActor*> props;
	vol->GetOverlappingActors(props, APropaneTank::StaticClass());

	if (!bDone && props.Num() == maxCanisters)
	{
		bDone = true;
		done();
	}

}