// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemys/EnemyAnimInstance.h"
#include "Characters/Enemys/Enemy.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Enemy = Cast<AEnemy>(TryGetPawnOwner());
}

void UEnemyAnimInstance::UpdateAnim()
{
	if (Enemy == nullptr)
	{
		Enemy = Cast<AEnemy>(TryGetPawnOwner());
	}
	if (Enemy)
	{
		const FVector SpeedVector = Enemy->GetVelocity();
		const FVector PlaneSpeed = FVector(SpeedVector.X, SpeedVector.Y, 0.0f);
		Speed = PlaneSpeed.Size();

		//float Direction =  CalculateDirection(Enemy->GetVelocity(), Enemy->GetActorRotation());
	}
}
