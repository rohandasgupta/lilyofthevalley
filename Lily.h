// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Lily.generated.h"

UCLASS()
class LILYOFTHEVALLEY_API ALily : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALily();

	class ALilyPlayerController* mainPlayerController;

	UPROPERTY(BlueprintReadOnly)
	float sens = 0.75f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UCameraComponent* followCamera;

	UPROPERTY(BlueprintReadOnly)
	class USpringArmComponent* cameraBoom;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBoxComponent* LFootstep;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBoxComponent* RFootstep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* step;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInteracting;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APropaneTank* tank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APropaneTank* currentTank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APropaneTank* oldTank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHolding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APropaneTank* tankHeld;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TankRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AShrineCandle* candle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AShrineCandle* oldCandle;

	bool candleswapped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACampfireBase* camp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACampfireBase* oldCamp;

	bool campswapped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ARobot* robot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ARobot* oldRobot;

	bool robotswapped = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AhighlightBase* highlight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AhighlightBase* oldHighlight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool canmandr = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> outlines;

	//Set of vars to query the end of the game

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDroneDone = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRobotDone = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCampfireDone = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bWeatherDone = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTransmitterDone = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDishDone = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTanksDone = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTreesDone = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTagsDone = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCandleDone = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int objectivesComplete = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShowPrompt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanInteract = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void interact();

	UFUNCTION(BlueprintCallable)
	void endInteract();

	UFUNCTION()
	void moveForward(float value);

	UFUNCTION()
	void moveRight(float value);

	UFUNCTION()
	void lookUp(float value);

	UFUNCTION()
	void turn(float value);

	UFUNCTION(BlueprintCallable)
	void footstep(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void clearAllOutlines();

};
