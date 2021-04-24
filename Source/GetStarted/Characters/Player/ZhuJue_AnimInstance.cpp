// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/ZhuJue_AnimInstance.h"

void UZhuJue_AnimInstance::NativeInitializeAnimation()
{
	Player = Cast<AZhuJue_Character>(TryGetPawnOwner());
}

void UZhuJue_AnimInstance::UpdateAnimationProperties()
{
	if (Player == nullptr)
	{
		Player = Cast<AZhuJue_Character>(TryGetPawnOwner());
	}
	if (Player)
	{
		FVector SpeedVector = Player->GetVelocity(); //获取到向量
		FVector XYSpeed = FVector(SpeedVector.X, SpeedVector.Y, 0.0f); //不需要x轴方向的向量
		Speed = XYSpeed.Size();  //向量转换为大小

		bIsFall = Player->GetMovementComponent()->IsFalling();  //判断是否在掉落状态
	}
}
