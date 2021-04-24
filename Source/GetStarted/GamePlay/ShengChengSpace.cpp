// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/ShengChengSpace.h"

// Sets default values
AShengChengSpace::AShengChengSpace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShengChengBoxCmp = CreateDefaultSubobject<UBoxComponent>(TEXT("ShengChengBoxCmp"));
	RootComponent = ShengChengBoxCmp;

}

// Called when the game starts or when spawned
void AShengChengSpace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShengChengSpace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AShengChengSpace::GetShengChengWeiZhi()
{
	FVector YuanDian = ShengChengBoxCmp->GetComponentLocation();
	FVector BianJie = ShengChengBoxCmp->GetScaledBoxExtent();

	//在盒子中随机生成点，需要两个参数，一个是原点，第二个是盒子长宽高
	return UKismetMathLibrary::RandomPointInBoundingBox(YuanDian, BianJie);
}

TSubclassOf<AActor> AShengChengSpace::GetActorClass()
{
	if (ActorClassesArray.Num() > 0)
	{
		int Index = FMath::RandRange(0, ActorClassesArray.Num() - 1);
		return ActorClassesArray[Index];
	}
	else
	{
		return nullptr;
	}
}

void AShengChengSpace::ShengChengActor_Implementation(UClass* ActorClass, FVector ActorLocation)
{
	if (ActorClass)
	{
		GetWorld()->SpawnActor<AActor>(ActorClass, ActorLocation, FRotator::ZeroRotator);
	}
}
	

