// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class UGameplayWidget;

UCLASS()
class CRUNCH_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// only called on the client
	virtual void AcknowledgePossession(class APawn* NewPawn) override;
	



protected:
	// only called on the server, also on the listening server.
	virtual void OnPossess(APawn* InPawn) override;
	
private:
	void SpawnGameplayWidget();
	
	UPROPERTY()
	class ACPlayerCharacter* CPlayerCharacter;
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UGameplayWidget> GameplayWidgetClass;
	
	UPROPERTY()
	UGameplayWidget* GameplayWidget;
};