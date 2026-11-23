// Fill out your copyright notice in the Description page of Project Settings.

#include "Crunch/Public/Character/CCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/CAbilitySystemComponent.h"
#include "GAS/CAttributeSet.h"

ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	bUseControllerRotationPitch=false;
	bUseControllerRotationRoll=false;
	bUseControllerRotationYaw=false;
	
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	GetCharacterMovement()->bOrientRotationToMovement=true;
	
	
	
	
	CAbilitySystemComponent=CreateDefaultSubobject<UCAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	CAttributeSet=CreateDefaultSubobject<UCAttributeSet>("CAttributeSet");
}

UAbilitySystemComponent* ACCharacter::GetAbilitySystemComponent() const
{
	return CAbilitySystemComponent;
}

void ACCharacter::ServerSideInit()
{
	CAbilitySystemComponent->InitAbilityActorInfo(this, this);
	CAbilitySystemComponent->ApplyInitialEffects();
}

void ACCharacter::ClientSideInit()
{
	CAbilitySystemComponent->InitAbilityActorInfo(this, this);
}