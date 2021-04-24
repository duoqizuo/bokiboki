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
		FVector SpeedVector = Player->GetVelocity(); //��ȡ������
		FVector XYSpeed = FVector(SpeedVector.X, SpeedVector.Y, 0.0f); //����Ҫx�᷽�������
		Speed = XYSpeed.Size();  //����ת��Ϊ��С

		bIsFall = Player->GetMovementComponent()->IsFalling();  //�ж��Ƿ��ڵ���״̬
	}
}
