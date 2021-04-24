// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/JiaoHuXiTong.h"

// Sets default values
AJiaoHuXiTong::AJiaoHuXiTong()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChuFaSphereCmp = CreateDefaultSubobject<USphereComponent>(TEXT("ChuFaSphereCmp"));
	RootComponent = ChuFaSphereCmp;

	ChuFaSphereCmp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ChuFaSphereCmp->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	ChuFaSphereCmp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ChuFaSphereCmp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	DisPlayMeshCmp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DisPlayMeshCmp"));
	DisPlayMeshCmp->SetupAttachment(GetRootComponent());

	IdleParticleCmp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("IdleParticleCmp"));
	DisPlayMeshCmp->SetupAttachment(GetRootComponent());

	bNeedRotator = true;
	RotatorSpeed = 45.0f;

}

// Called when the game starts or when spawned
void AJiaoHuXiTong::BeginPlay()
{
	Super::BeginPlay();
	
	ChuFaSphereCmp->OnComponentBeginOverlap.AddDynamic(this, &AJiaoHuXiTong::OnOverlapBegin);
	ChuFaSphereCmp->OnComponentEndOverlap.AddDynamic(this, &AJiaoHuXiTong::OnOverlapEnd);

}

// Called every frame
void AJiaoHuXiTong::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bNeedRotator)
	{
		FRotator NewRotator = GetActorRotation();
		NewRotator.Yaw += RotatorSpeed * DeltaTime;
		SetActorRotation(NewRotator);
	}

}

void AJiaoHuXiTong::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AJiaoHuXiTong::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

