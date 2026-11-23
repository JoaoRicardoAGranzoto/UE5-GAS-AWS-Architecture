// Fill out your copyright notice in the Description page of Project Settings.

#include "Crunch/Public/Player/CPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACPlayerCharacter::ACPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled=false;
	
	CameraBoom=CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bUsePawnControlRotation=true;
	
	ViewCam=CreateDefaultSubobject<UCameraComponent>("View Cam");
	
	
	
	
	ViewCam->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	ViewCam->bUsePawnControlRotation=false;
}

void ACPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController=Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem=PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(CrunchInputContext, 0);
		}
	}
	
	UEnhancedInputComponent* CrunchInputComponent=CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	
	CrunchInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	CrunchInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	CrunchInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ThisClass::Jump);
}

void ACPlayerCharacter::Move(const struct FInputActionValue& AxisValue)
{
	const FVector2D Value = AxisValue.Get<FVector2D>();
	
	const FRotator MovementRotation=FRotator(0.f, GetControlRotation().Yaw, 0.f);
	
	const FVector ForwardDirection=MovementRotation.RotateVector(FVector::ForwardVector);
	const FVector RightDirection=MovementRotation.RotateVector(FVector::RightVector);

	AddMovementInput(ForwardDirection,Value.X);
	AddMovementInput(RightDirection,Value.Y);



}

void ACPlayerCharacter::Look(const struct FInputActionValue& AxisValue)
{
	AddControllerYawInput(AxisValue.Get<FVector2D>().X);
	AddControllerPitchInput(AxisValue.Get<FVector2D>().Y);
}