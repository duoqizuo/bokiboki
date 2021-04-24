// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/JiGuanMen_Actor.h"

// Sets default values
AJiGuanMen_Actor::AJiGuanMen_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	JiGuanBoxCmp = CreateDefaultSubobject<UBoxComponent>(TEXT("JiGuanBoxCmp"));
	RootComponent = JiGuanBoxCmp;

	JiGuanBoxCmp->SetBoxExtent(FVector(60.0f, 60.0f, 30.0f));

	JiGuanBoxCmp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	JiGuanBoxCmp->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	JiGuanBoxCmp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	JiGuanBoxCmp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	DoorMeshCmp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMeshCmp"));
	DoorMeshCmp->SetupAttachment(GetRootComponent());

	JiGuanMeshCmp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("JiGuanMeshCmp"));
	JiGuanMeshCmp->SetupAttachment(GetRootComponent());

	YanShiTime = 1.0f;
}

// Called when the game starts or when spawned
void AJiGuanMen_Actor::BeginPlay()
{
	Super::BeginPlay();
	
	JiGuanBoxCmp->OnComponentBeginOverlap.AddDynamic(this, &AJiGuanMen_Actor::OnJiGuanBeginBox);
	JiGuanBoxCmp->OnComponentEndOverlap.AddDynamic(this, &AJiGuanMen_Actor::OnJiGuanEndBox);

	InitJiGuanLocation = JiGuanMeshCmp->GetComponentLocation();
	InitDoorLocation = DoorMeshCmp->GetComponentLocation();
}

// Called every frame
void AJiGuanMen_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJiGuanMen_Actor::OnJiGuanBeginBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const AZhuJue_Character* ZhuJue = Cast<AZhuJue_Character>(OtherActor);
	if (ZhuJue)
	{
		GetWorldTimerManager().ClearTimer(JiGuanMenTimeHandle);
		CaiXiaJiGuan();
		OpenDoor();
	}
}

void AJiGuanMen_Actor::OnJiGuanEndBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const AZhuJue_Character* ZhuJue = Cast<AZhuJue_Character>(OtherActor);
	if (ZhuJue)
	{
		LiKaiJiGuan();
		//第一个句柄，第二个哪个类，第三个哪一个方法,第四个延迟多久时间
		GetWorldTimerManager().SetTimer(JiGuanMenTimeHandle, this, &AJiGuanMen_Actor::CloseDoor, YanShiTime, false);
	}
}

void AJiGuanMen_Actor::UpdateJiGuanLocation(FVector offset)
{
	FVector NewLocation = InitJiGuanLocation + offset;
	JiGuanMeshCmp->SetWorldLocation(NewLocation);
}

void AJiGuanMen_Actor::UpdateDoorLocation(FVector offset)
{
	FVector NewLocation = InitDoorLocation + offset;
	DoorMeshCmp->SetWorldLocation(NewLocation);
}

