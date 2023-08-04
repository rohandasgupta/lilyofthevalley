// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "highlightBase.generated.h"

UCLASS()
class LILYOFTHEVALLEY_API AhighlightBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AhighlightBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSwapped = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintImplementableEvent)
	void customRender(bool b);

	UFUNCTION(BlueprintImplementableEvent)
	void action();
};
