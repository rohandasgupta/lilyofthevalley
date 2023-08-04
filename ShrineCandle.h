// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShrineCandle.generated.h"

UCLASS()
class LILYOFTHEVALLEY_API AShrineCandle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShrineCandle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* lantern;

	bool swapped = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* lanternSpawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void customRender(bool b);

	UFUNCTION(BlueprintImplementableEvent)
	void swap();
};

