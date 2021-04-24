// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/Level1_GameMode.h"

ALevel1_GameMode::ALevel1_GameMode()
{
}

void ALevel1_GameMode::BeginPlay()
{
	Super::BeginPlay();

	if (ZhuJueUIClass)
	{
		//��һ��������һ������ӵ������ʹ��UGameplayStatics��ȡ����ǰ��ң�this��ʾ��˭������,
		//�ڶ���Ҫ������һ�����͵�UUserWidget
		ZhuJueUI = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(this, 0), ZhuJueUIClass);
		//��ӵ��ӿ�
		if (ZhuJueUI)
		{
			ZhuJueUI->AddToViewport();
		}
	}
}
