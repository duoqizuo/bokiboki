// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/Player/ZhuJue_Character.h"
#include "CoreMinimal.h"
#include "GamePlay/JiaoHuXiTong.h"
#include "ShiQuWu.generated.h"

/**
 * 
 */
UCLASS()
class GETSTARTED_API AShiQuWu : public AJiaoHuXiTong
{
	GENERATED_BODY()
	
public:

	AShiQuWu();

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "ShiQu")
	void ShiQu(AZhuJue_Character* ZhuJue);

};
