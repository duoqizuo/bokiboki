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
		//第一个参数哪一个物体拥有它（使用UGameplayStatics获取到当前玩家，this表示是谁在请求）,
		//第二个要生产哪一个类型的UUserWidget
		ZhuJueUI = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(this, 0), ZhuJueUIClass);
		//添加到视口
		if (ZhuJueUI)
		{
			ZhuJueUI->AddToViewport();
		}
	}
}
