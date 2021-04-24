// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/FuDongPingTai.h"

// Sets default values
AFuDongPingTai::AFuDongPingTai()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PingTaiMeshCmp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PingTaiMeshCmp"));
	RootComponent = PingTaiMeshCmp;

	StartPoint = FVector(0.0f);
	EndPoint = FVector(0.0f);

	Speed = 2.0f;

	TingLiuTime = 2.0f;

	bIsTingLiu = false;
}

// Called when the game starts or when spawned
void AFuDongPingTai::BeginPlay()
{
	Super::BeginPlay();
	
	StartPoint = GetActorLocation();
	EndPoint += StartPoint;

	JuLi = (EndPoint - StartPoint).Size();
}

// Called every frame
void AFuDongPingTai::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsTingLiu)
	{
		const FVector CurrentLocation = GetActorLocation();
		//第一个参数当前位置，第二个目标点位置，第三个帧，第四个速度,返回一个当前应该在的位置
		const FVector NewLocation = FMath::VInterpTo(CurrentLocation, EndPoint, DeltaTime, Speed);
		SetActorLocation(NewLocation);

		const float NewJuLi = (GetActorLocation() - StartPoint).Size();
		if (JuLi - NewJuLi <= 0.5f)
		{
			bIsTingLiu = true;

			const FVector SwapWeiZhi = StartPoint;
			StartPoint = EndPoint;
			EndPoint = SwapWeiZhi;

			const auto SwapPoint = [this]()
			{
				bIsTingLiu = false;
			};
			GetWorldTimerManager().SetTimer(TingLiuTimerHandle, FTimerDelegate::CreateLambda(SwapPoint), TingLiuTime, false);
		}
	}
}

