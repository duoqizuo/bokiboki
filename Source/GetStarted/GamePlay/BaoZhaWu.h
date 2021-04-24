// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/Player/ZhuJue_Character.h"
#include "CoreMinimal.h"
#include "GamePlay/JiaoHuXiTong.h"
#include "BaoZhaWu.generated.h"

/**
 * 
 */
UCLASS()
class GETSTARTED_API ABaoZhaWu : public AJiaoHuXiTong
{
	GENERATED_BODY()
	
public:

	ABaoZhaWu();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaoZha|ShangHai")
	float BaoZhaShangHai;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaoZha|ShangHai")
	TSubclassOf<UDamageType> ShangHaiClass;
public:
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
