// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GetStartedGameModeBase.h"
#include "Level1_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class GETSTARTED_API ALevel1_GameMode : public AGetStartedGameModeBase
{
	GENERATED_BODY()

public:

	ALevel1_GameMode();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<class UUserWidget> ZhuJueUIClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UMG")
	UUserWidget* ZhuJueUI;

protected:
	virtual void BeginPlay() override;

};
