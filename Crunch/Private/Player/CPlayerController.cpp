// Fill out your copyright notice in the Description page of Project Settings.

#include "Crunch/Public/Player/CPlayerController.h"
#include "Widgets/GameplayWidget.h"
#include "Player/CPlayerCharacter.h"

void ACPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	CPlayerCharacter = Cast<ACPlayerCharacter>(InPawn);
	if (CPlayerCharacter)
	{
		CPlayerCharacter->ServerSideInit();
	}
}

void ACPlayerController::AcknowledgePossession(class APawn* NewPawn)




{
	Super::AcknowledgePossession(NewPawn);
	
	CPlayerCharacter=Cast<ACPlayerCharacter>(NewPawn);
	if (CPlayerCharacter)
	{
		CPlayerCharacter->ClientSideInit();
		SpawnGameplayWidget();
	}
}

void ACPlayerController::SpawnGameplayWidget()
{
	if (!IsLocalPlayerController()) return;
	
	GameplayWidget=CreateWidget<UGameplayWidget>(this, GameplayWidgetClass);
}