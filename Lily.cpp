// Fill out your copyright notice in the Description page of Project Settings.


#include "Lily.h"
#include "LilyPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "PropaneTank.h"
#include "Components/StaticMeshComponent.h"
#include "Math/Vector.h"
#include "ShrineCandle.h"
#include "CampfireBase.h"
#include "highlightBase.h"
#include "Robot.h"

// Sets default values
ALily::ALily()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	cameraBoom->SetupAttachment(GetRootComponent());

	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	followCamera->SetupAttachment(cameraBoom);

	cameraBoom->TargetArmLength = 400.f;
	cameraBoom->bUsePawnControlRotation = true;
	cameraBoom->bEnableCameraLag = true;
	cameraBoom->CameraLagSpeed = 10;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.2;

	LFootstep = CreateDefaultSubobject<UBoxComponent>(TEXT("LFootstep"));
	RFootstep = CreateDefaultSubobject<UBoxComponent>(TEXT("RFootstep"));

	LFootstep->SetupAttachment(GetMesh(), FName("LeftFootSocket"));
	RFootstep->SetupAttachment(GetMesh(), FName("RightFootSocket"));

	LFootstep->SetBoxExtent(FVector(10.f, 5.f, 3.f));
	RFootstep->SetBoxExtent(FVector(10.f, 5.f, 3.f));

	// location and rotation to be adjusted in editor

	LFootstep->OnComponentBeginOverlap.AddDynamic(this, &ALily::footstep);
	RFootstep->OnComponentBeginOverlap.AddDynamic(this, &ALily::footstep);
	
	TankRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Root"));
	TankRoot->SetupAttachment(GetMesh(), FName("RightHandSocket"));
}

// Called when the game starts or when spawned
void ALily::BeginPlay()
{
	Super::BeginPlay();
	
	mainPlayerController = Cast<ALilyPlayerController>(GetController());

	if (IsValid(mainPlayerController))
	{
		if (IsValid(mainPlayerController->PlayerCameraManager)){
			mainPlayerController->PlayerCameraManager->ViewPitchMin = -60;
			mainPlayerController->PlayerCameraManager->ViewPitchMax = 60;
		}
	}

}

// Called every frame
void ALily::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult OutHit;
	FVector Start = followCamera->GetComponentLocation();

	// alternatively you can get the camera location
	// FVector Start = FirstPersonCameraComponent->GetComponentLocation();

	FVector ForwardVector = followCamera->GetForwardVector();
	FVector End = ((ForwardVector * 1250.f) + Start);
	FCollisionQueryParams CollisionParams;
	if (!bHolding)
	{
		if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams))
		{
			if (OutHit.bBlockingHit)
			{
				oldTank = tank;
				tank = Cast<APropaneTank>(OutHit.GetActor());

				if (IsValid(tank) && IsValid(oldTank))
				{
					currentTank = tank;
					if (tank != oldTank)
					{
						oldTank->customRender(false);
						tank->customRender(true);
					}
				}
				else if (IsValid(tank))
				{
					tank->customRender(true);
					currentTank = tank;
					bShowPrompt = true;
				}
				else if (IsValid(oldTank))
				{
					oldTank->customRender(false);
					currentTank = nullptr;
					bShowPrompt = false;
				}

				oldCandle = candle;
				candle = Cast<AShrineCandle>(OutHit.GetActor());

				if (IsValid(candle))
				{
					if (!candleswapped)
					{
						candle->customRender(true);
						bShowPrompt = true;
					}
				}
				else if (IsValid(oldCandle))
				{
					oldCandle->customRender(false);
					bShowPrompt = false;
				}

				oldCamp = camp;
				camp = Cast<ACampfireBase>(OutHit.GetActor());

				if (IsValid(camp))
				{
					if (!campswapped)
					{
						camp->customRender(true);
						bShowPrompt = true;
					}
				}
				else if (IsValid(oldCamp))
				{
					oldCamp->customRender(false);
					bShowPrompt = false;
				}

				oldRobot = robot;
				robot = Cast<ARobot>(OutHit.GetActor());

				if (IsValid(robot))
				{
					if (!robotswapped)
					{
						robot->customRender(true);
						bShowPrompt = true;
					}
				}
				else if (IsValid(oldRobot))
				{
					oldRobot->customRender(false);
					bShowPrompt = false;
				}

				oldHighlight = highlight;
				highlight = Cast<AhighlightBase>(OutHit.GetActor());

				if (IsValid(highlight))
				{
					if (!highlight->bSwapped)
					{
						highlight->customRender(true);
						bShowPrompt = true;
					}
				}
				else if (IsValid(oldHighlight))
				{
					oldHighlight->customRender(false);
					bShowPrompt = false;
				}

			}
		}
		else
		{
			clearAllOutlines();
		}
	}
	else
	{
		if (IsValid(tank))
		{
			tank->customRender(false);
		}
		if (IsValid(oldTank))
		{
			oldTank->customRender(false);
		}
		if (IsValid(currentTank))
		{
			currentTank->customRender(false);
		}
		currentTank->SetActorLocation(TankRoot->GetComponentLocation());
		currentTank->SetActorRotation(TankRoot->GetComponentRotation());
		currentTank->SetActorScale3D(FVector(22.f, 22.f, 22.f));
	}
}

// Called to bind functionality to input
void ALily::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ALily::interact);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &ALily::endInteract);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALily::moveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALily::moveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ALily::lookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ALily::turn);
}

void ALily::interact()
{
	if (bCanInteract) {
		bInteracting = true;
		if (IsValid(currentTank))
		{
			if (bHolding)
			{
				currentTank->Mesh1->SetSimulatePhysics(true);
				currentTank->SetActorEnableCollision(true);
				bHolding = false;
				GetCharacterMovement()->MaxWalkSpeed = 500.f;
			}
			else
			{
				currentTank->Mesh1->SetSimulatePhysics(false);
				currentTank->SetActorEnableCollision(false);
				bHolding = true;
				GetCharacterMovement()->MaxWalkSpeed = 300.f;
			}
		}
		if (IsValid(candle))
		{
			candle->swap();
			candleswapped = true;
			candle->customRender(false);
		}
		if (IsValid(camp) && !campswapped)
		{
			camp->swap();
			campswapped = true;
			camp->customRender(false);
		}
		if (IsValid(robot) && !robotswapped)
		{
			robot->action();
			robotswapped = true;
			robot->customRender(false);
		}
		if (IsValid(highlight))
		{
			if (!highlight->bSwapped)
			{
				highlight->action();
				highlight->bSwapped = true;
				highlight->customRender(false);
				bShowPrompt = false;
			}
		}
	}
}

void ALily::endInteract()
{
	bInteracting = false;
}

void ALily::moveForward(float value)
{
	if (canmandr) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void ALily::moveRight(float value)
{
	if (canmandr) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void ALily::lookUp(float value)
{
	if (mainPlayerController&&canmandr)
	{
		AddControllerPitchInput(value * sens);
	}
}

void ALily::turn(float value)
{
	if (mainPlayerController&&canmandr)
	{
		AddControllerYawInput(value);
	}
}

void ALily::footstep(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((GetMovementComponent()->Velocity).Length() > 0.5)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), step, 0.4f, 0.75f, 0.3f);
	}
}

void ALily::clearAllOutlines()
{
	bShowPrompt = false;
	for (AActor* a : outlines)
	{
		ARobot* r = Cast<ARobot>(a);
		if (IsValid(r))
		{
			r->customRender(false);
		}
		ACampfireBase* ca = Cast<ACampfireBase>(a);
		if (IsValid(ca))
		{
			ca->customRender(false);
		}
		AShrineCandle* s = Cast<AShrineCandle>(a);
		if (IsValid(s))
		{
			s->customRender(false);
		}
		APropaneTank* p = Cast<APropaneTank>(a);
		if (IsValid(p))
		{
			p->customRender(false);
		}
		AhighlightBase* h = Cast<AhighlightBase>(a);
		if (IsValid(h))
		{
			h->customRender(false);
			
		}
	}
}