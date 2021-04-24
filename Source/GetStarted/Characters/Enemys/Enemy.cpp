// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemys/Enemy.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Characters/Player/ZhuJue_Character.h"
#include "AIController.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Sound/SoundCue.h"
#include "TimerManager.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = 500.0f;

	//防止怪物阻挡相机
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	ChaseVolumeCmp = CreateDefaultSubobject<USphereComponent>(TEXT("ChaseVolumeCmp"));
	ChaseVolumeCmp->SetupAttachment(GetRootComponent());
	ChaseVolumeCmp->InitSphereRadius(800.0f);
	ChaseVolumeCmp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ChaseVolumeCmp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	ChaseVolumeCmp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ChaseVolumeCmp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	AttackVolumeCmp = CreateDefaultSubobject<USphereComponent>(TEXT("AttackVolumeCmp"));
	AttackVolumeCmp->SetupAttachment(GetRootComponent());
	AttackVolumeCmp->InitSphereRadius(100.0f);
	AttackVolumeCmp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AttackVolumeCmp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	AttackVolumeCmp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AttackVolumeCmp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	HealthBarWidgetCmp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidgetCmp"));
	HealthBarWidgetCmp->SetupAttachment(GetRootComponent());
	//设置空间
	HealthBarWidgetCmp->SetWidgetSpace(EWidgetSpace::Screen);
	//设置大小
	HealthBarWidgetCmp->SetDrawSize(FVector2D(125.0f, 10.f));

	LeftAttackSocketCmp = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftAttackSocketCmp"));
	LeftAttackSocketCmp->SetupAttachment(GetMesh(), "LeftAttackSocket");
	DeactiveLeftAttackCollision();

	RightAttackSocketCmp = CreateDefaultSubobject<UBoxComponent>(TEXT("RightAttackSocketCmp"));
	RightAttackSocketCmp->SetupAttachment(GetMesh(), "RightAttackSocket");
	DeactiveRightAttackCollision();

	EnemyStatus = EEnemyStatus::EES_Idle;

	//自动持有AI
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bIsAttackVolume = false;

	InterpSpeed = 15.0f;
	bInterpToPlayer = false;

	MaxHealth = 100.0f;
	Health = MaxHealth;

	AttackDamage = 10.0f;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	ChaseVolumeCmp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnChaseVolumeOverlapBegin);
	ChaseVolumeCmp->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnChaseVolumeOverlapEnd);

	AttackVolumeCmp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnAttackVolumeOverlapBegin);
	AttackVolumeCmp->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnAttackVolumeOverlapEnd);
	
	AIController = Cast<AAIController>(GetController()); 
	 
	HealthBar = Cast<UProgressBar>(HealthBarWidgetCmp->GetUserWidgetObject()->GetWidgetFromName("Health"));
	HealthBar->SetPercent(Health / MaxHealth);
	HealthBar->SetVisibility(ESlateVisibility::Hidden);

	LeftAttackSocketCmp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnLeftAttackOverlapBegin);
	LeftAttackSocketCmp->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnLeftAttackOverlapEnd);

	RightAttackSocketCmp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnRightAttackOverlapBegin);
	RightAttackSocketCmp->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnRightAttackOverlapEnd);

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInterpToPlayer && IsTarget() && !IsDeath())
	{
		const FRotator LookAtYaw(0.0f, UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation()).Yaw, 0.0f);
		const FRotator InterpRotator = FMath::RInterpTo(GetActorRotation(), LookAtYaw, DeltaTime, InterpSpeed);
		SetActorRotation(InterpRotator);
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnChaseVolumeOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && !IsDeath())
	{
		AZhuJue_Character* MainPlay = Cast<AZhuJue_Character>(OtherActor);
		if (MainPlay)
		{
			HealthBar->SetVisibility(ESlateVisibility::Visible);
			ChasePlayer(MainPlay);
		}
	}
}

void AEnemy::OnChaseVolumeOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && !IsDeath())
	{
		AZhuJue_Character* MainPlayer = Cast<AZhuJue_Character>(OtherActor);
		if (MainPlayer)
		{
			HealthBar->SetVisibility(ESlateVisibility::Hidden);
			EnemyStatus = EEnemyStatus::EES_Idle;

			if (AIController)
			{
				AIController->StopMovement();
			}
		}
	}
}

void AEnemy::OnAttackVolumeOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && !IsDeath())
	{
		AZhuJue_Character* MainPlayer = Cast<AZhuJue_Character>(OtherActor);
		if (MainPlayer)
		{
			MainPlayer->UpdateAttackTarget();
			bIsAttackVolume = true;
			Attack();
		}
	}
}

void AEnemy::OnAttackVolumeOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && !IsDeath())
	{
		AZhuJue_Character* MainPlayer = Cast<AZhuJue_Character>(OtherActor);
		if (MainPlayer)
		{
			bIsAttackVolume = false;
			if (EnemyStatus != EEnemyStatus::EES_Attack)
			{
				ChasePlayer(MainPlayer);
			}
		}
	}
}

void AEnemy::ChasePlayer(AZhuJue_Character* TargetPlayer)
{
	if (!IsDeath() && IsTarget())
	{
		EnemyStatus = EEnemyStatus::EES_Chase;

		if (AIController)
		{
			FAIMoveRequest AIMoveRequest;
			//追逐的目标
			AIMoveRequest.SetGoalActor(TargetPlayer);
			//接受半径,距离多近算追逐成功，停止
			AIMoveRequest.SetAcceptanceRadius(10.0f);

			//将找到的路径点返回到这里面
			FNavPathSharedPtr NavPathSharedPtr;

			//返回导航路径，第一个参数是移动的请求，第二个是移动导航的指针
			AIController->MoveTo(AIMoveRequest, &NavPathSharedPtr);
		}
	}
}

void AEnemy::Attack()
{
	if (IsTarget() && !IsDeath())
	{
		if (AIController)
		{
			AIController->StopMovement();
		}
		if (EnemyStatus != EEnemyStatus::EES_Attack)
		{
			EnemyStatus = EEnemyStatus::EES_Attack;
			bInterpToPlayer = true;

			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance && AttackMontage)
			{
				const float PlayRate = FMath::RandRange(0.5f, 0.6f);
				const FString AnimName = FString::FromInt(FMath::RandRange(1, 3));
				AnimInstance->Montage_Play(AttackMontage, PlayRate);
				AnimInstance->Montage_JumpToSection(FName(*AnimName), AttackMontage);
			}
		}
	}
}

void AEnemy::AttackEnd()
{
	bInterpToPlayer = false;
	if (!IsDeath())
	{
		EnemyStatus = EEnemyStatus::EES_Idle;
		if (bIsAttackVolume && IsTarget())
		{
			Attack();
		}
	}	
}

void AEnemy::OnLeftAttackOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && !IsDeath())
	{
		AZhuJue_Character* MainPlay = Cast<AZhuJue_Character>(OtherActor);
		if (MainPlay)
		{
			if (MainPlay->HitParticle)
			{
				const USkeletalMeshSocket* AttackSocket = GetMesh()->GetSocketByName("LeftAttackSocket");
				if (AttackSocket)
				{
					FVector SocketLocation = AttackSocket->GetSocketLocation(GetMesh());
					UGameplayStatics::SpawnEmitterAtLocation(this, MainPlay->HitParticle, SocketLocation, FRotator(0.0f), true);
				}
			}
			if (MainPlay->HitSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, MainPlay->HitSound, MainPlay->GetActorLocation());
			}
			if (DamageTypeClass)
			{
				UGameplayStatics::ApplyDamage(MainPlay, AttackDamage / 2.0f, AIController, this, DamageTypeClass);
			}
		}
	}
}

void AEnemy::OnLeftAttackOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AEnemy::OnRightAttackOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && !IsDeath())
	{
		AZhuJue_Character* MainPlay = Cast<AZhuJue_Character>(OtherActor);
		if (MainPlay)
		{
			if (MainPlay->HitParticle)
			{
				const USkeletalMeshSocket* AttackSocket = GetMesh()->GetSocketByName("RightAttackSocket");
				if (AttackSocket)
				{
					FVector SocketLocation = AttackSocket->GetSocketLocation(GetMesh());
					UGameplayStatics::SpawnEmitterAtLocation(this, MainPlay->HitParticle, SocketLocation, FRotator(0.0f), true);
				}
			}
			if (MainPlay->HitSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, MainPlay->HitSound, MainPlay->GetActorLocation());
			}
			if (DamageTypeClass)
			{
				UGameplayStatics::ApplyDamage(MainPlay, AttackDamage / 2.0f, AIController, this, DamageTypeClass);
			}
		}
	}
}

void AEnemy::OnRightAttackOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AEnemy::ActiveLeftAttackCollision()
{
	LeftAttackSocketCmp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LeftAttackSocketCmp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	LeftAttackSocketCmp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LeftAttackSocketCmp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AEnemy::DeactiveLeftAttackCollision()
{
	LeftAttackSocketCmp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemy::ActiveRightAttackCollision()
{
	RightAttackSocketCmp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RightAttackSocketCmp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightAttackSocketCmp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightAttackSocketCmp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AEnemy::DeactiveRightAttackCollision()
{
	RightAttackSocketCmp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

float AEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health = FMath::Clamp(Health -= Damage, 0.0f, MaxHealth);
	if (Health <= 0.0f)
	{
		Die();
	}

	HealthBar->SetPercent(Health / MaxHealth);

	return Health;
}

void AEnemy::Die()
{
	EnemyStatus = EEnemyStatus::EES_Dead;

	HealthBar->SetVisibility(ESlateVisibility::Hidden);

	DeactiveLeftAttackCollision();
	DeactiveRightAttackCollision();
	ChaseVolumeCmp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackVolumeCmp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Cast<AZhuJue_Character>(UGameplayStatics::GetPlayerPawn(this, 0))->UpdateAttackTarget();
}

void AEnemy::DeathEnd()
{
	GetMesh()->bPauseAnims = true;
	GetMesh()->bNoSkeletonUpdate = true;

	FTimerHandle DeathHandle;
	auto DeathDestroy = [this]()
	{
		Destroy();
	};
	GetWorldTimerManager().SetTimer(DeathHandle, FTimerDelegate::CreateLambda(DeathDestroy), 1.0f, false);
}

bool AEnemy::IsTarget()
{
	return Cast<AZhuJue_Character>(UGameplayStatics::GetPlayerPawn(this, 0))->ZhuJueStatus!=EZhuJueStatus::EZJS_Dead;
}

