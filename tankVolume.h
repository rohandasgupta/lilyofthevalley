// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "tankVolume.generated.h"

UCLASS()
class LILYOFTHEVALLEY_API AtankVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AtankVolume();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int maxCanisters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int canisters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* vol;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bDone;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void done();
};
