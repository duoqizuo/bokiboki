// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/Player/ZhuJue_Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ZhuJue_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GETSTARTED_API UZhuJue_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anim | ZhuangTai")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anim | ZhuangTai")
	bool bIsFall;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anim")
	AZhuJue_Character* Player;

public:

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "Anim")
	void UpdateAnimationProperties();
};
