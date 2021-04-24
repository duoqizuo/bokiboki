// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GETSTARTED_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Speed")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	class AEnemy* Enemy;

public:

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "Anim")
	void UpdateAnim();

};
