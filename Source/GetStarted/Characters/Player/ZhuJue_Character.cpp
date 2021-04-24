// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/ZhuJue_Character.h"
#include "GamePlay/Weapon_Actor.h"
#include "Characters/Enemys/Enemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"

// Sets default values
AZhuJue_Character::AZhuJue_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	GetCapsuleComponent()->InitCapsuleSize(35.0f, 100.0f); 

	SpringArmCmp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmCmp"));
	SpringArmCmp->SetupAttachment(GetRootComponent());
	SpringArmCmp->TargetArmLength = 300.0f;
	SpringArmCmp->bUsePawnControlRotation = true;

	CameraCmp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraCmp"));
	CameraCmp->SetupAttachment(SpringArmCmp, USpringArmComponent::SocketName);
	CameraCmp->bUsePawnControlRotation = false;

	MaxHealth = 100.0f;
	Health = MaxHealth;
	MaxNaiLi = 150.0f;
	NaiLi = MaxNaiLi;
	Coins = 0;

	NaiLiXiaoHao = 25.0f;
	NaiLiPiLaoRatio = 0.167f;

	RunningSpeed = 600.0f;
	ChongCiSpeed = 900.0f;

	ZhuJueStatus = EZhuJueStatus::EZJS_Normal;
	NaiLiStatus = ENaiLiStatus::ENLS_Normal;

	bOnShift = false;

	bAttackKeyDown = false;
	bIsAttack = false;

	AttackTarget = nullptr;

	InterpSpeed = 15.0f;
	bInterpToEnemy = false;

}

// Called when the game starts or when spawned
void AZhuJue_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZhuJue_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDeath())
	{
		return;
	}

	switch (NaiLiStatus)
	{
	case ENaiLiStatus::ENLS_Normal :
		if (bOnShift)
		{
			NaiLi = FMath::Clamp(NaiLi -= NaiLiXiaoHao * DeltaTime, 0.0f, MaxNaiLi);
			if (NaiLi <= MaxNaiLi * NaiLiPiLaoRatio)
			{
				NaiLiStatus = ENaiLiStatus::ENLS_WuNaiLi;
			}
			SetZhuJueStatus(EZhuJueStatus::EZJS_ChongCi);
		}
		else
		{
			NaiLi = FMath::Clamp(NaiLi += NaiLiXiaoHao * DeltaTime, 0.0f, MaxNaiLi);
			SetZhuJueStatus(EZhuJueStatus::EZJS_Normal);
		}
		break;
	case ENaiLiStatus::ENLS_WuNaiLi:
		if (bOnShift)
		{
			NaiLi = FMath::Clamp(NaiLi -= NaiLiXiaoHao * DeltaTime, 0.0f, MaxNaiLi);
			if (NaiLi <= 0.0f)
			{
				OnShiftUp();
				NaiLiStatus = ENaiLiStatus::ENLS_NaiLiHuiFu;
				SetZhuJueStatus(EZhuJueStatus::EZJS_Normal);
			}
		}
		else
		{
			NaiLiStatus = ENaiLiStatus::ENLS_NaiLiHuiFu;
			NaiLi = FMath::Clamp(NaiLi += NaiLiXiaoHao * DeltaTime, 0.0f, MaxNaiLi);
			SetZhuJueStatus(EZhuJueStatus::EZJS_Normal);
		}
		break;
	case ENaiLiStatus::ENLS_NaiLiHuiFu:
		OnShiftUp();
		NaiLi = FMath::Clamp(NaiLi += NaiLiXiaoHao * DeltaTime, 0.0f, MaxNaiLi);
		SetZhuJueStatus(EZhuJueStatus::EZJS_Normal);
		if (NaiLi >= MaxNaiLi * NaiLiPiLaoRatio)
		{
			NaiLiStatus = ENaiLiStatus::ENLS_Normal;
			SetZhuJueStatus(EZhuJueStatus::EZJS_Normal);
		}
		break;
	default:
		break;
	}
	if (bInterpToEnemy && AttackTarget)
	{
		//找到要看的物体应该怎么转向,参数起点，望向什么地方
		const FRotator LookAtYaw(0.0f, UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), AttackTarget->GetActorLocation()).Yaw, 0.0f);
		const FRotator InterpRotator = FMath::RInterpTo(GetActorRotation(), LookAtYaw, DeltaTime, InterpSpeed);
		SetActorRotation(InterpRotator);
	}

}

// Called to bind functionality to input
void AZhuJue_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AZhuJue_Character::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis(TEXT("Move_QianHou"), this, &AZhuJue_Character::Move_QianHou);
	PlayerInputComponent->BindAxis(TEXT("Move_ZuoYou"), this, &AZhuJue_Character::Move_ZuoYou);

	PlayerInputComponent->BindAxis(TEXT("Look_ZuoYou"), this, &AZhuJue_Character::Look_ZuoYou);
	PlayerInputComponent->BindAxis(TEXT("Look_ShangXia"), this, &AZhuJue_Character::Look_ShangXia);

	PlayerInputComponent->BindAction(TEXT("ChongCi"), IE_Pressed, this, &AZhuJue_Character::OnShiftDown);
	PlayerInputComponent->BindAction(TEXT("ChongCi"), IE_Released, this, &AZhuJue_Character::OnShiftUp);

	PlayerInputComponent->BindAction(TEXT("interaction"), IE_Pressed, this, &AZhuJue_Character::EZhuangBeiWeapon);

	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &AZhuJue_Character::AttackDown);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Released, this, &AZhuJue_Character::AttackUp);

}

void AZhuJue_Character::Jump()
{
	if(!IsDeath())
		Super::Jump();
}

void AZhuJue_Character::Move_QianHou(float value)
{
	if ((Controller != nullptr) && (value != 0.0f) && (!bIsAttack) && (!IsDeath()))
	{
		FRotator YawRotator(0, Controller->GetControlRotation().Yaw, 0);
		FVector Vector = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
		AddMovementInput(Vector, value);
	}
}

void AZhuJue_Character::Move_ZuoYou(float value)
{
	if ((Controller != nullptr) && (value != 0.0f) && (!bIsAttack) && (!IsDeath()))
	{
		FRotator YawRotator(0, Controller->GetControlRotation().Yaw, 0);
		FVector Vector = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);
		AddMovementInput(Vector, value);
	}
}

void AZhuJue_Character::Look_ShangXia(float value)
{
	if (GetControlRotation().Pitch < 270.0f && GetControlRotation().Pitch>180.0f && value > 0.0f)
		return;
	if (GetControlRotation().Pitch < 180.0f && GetControlRotation().Pitch>45.0f && value < 0.0f)
		return;
	AddControllerPitchInput(value);
}

void AZhuJue_Character::Look_ZuoYou(float value)
{
	if (GetControlRotation().Pitch < 270.0f && GetControlRotation().Pitch>180.0f && value > 0.0f)
		return;
	if (GetControlRotation().Pitch < 180.0f && GetControlRotation().Pitch>45.0f && value < 0.0f)
		return;
	AddControllerYawInput(value);
}

void AZhuJue_Character::AddHealth(float value)
{
	Health = FMath::Clamp(Health += value, 0.0f, MaxHealth);
}

void AZhuJue_Character::AddNaiLi(float value)
{
	//FMath::Clamp(NaiLi += value, 0.0f, MaxNaiLi);
	NaiLi = FMath::Clamp(NaiLi += value, 0.0f, MaxNaiLi);
}

void AZhuJue_Character::AddCoin(int value)
{
	Coins = FMath::Clamp(Coins += value, 0, 99999);
}

float AZhuJue_Character::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health = FMath::Clamp(Health -= Damage, 0.0f, MaxHealth);
	if (Health <= 0.0f)
	{
		Die();
	}

	return Health;
}

void AZhuJue_Character::SetZhuJueStatus(EZhuJueStatus status)
{
	if (!IsDeath())
	{
		ZhuJueStatus = status;
		switch (ZhuJueStatus)
		{
		case EZhuJueStatus::EZJS_ChongCi:
			GetCharacterMovement()->MaxWalkSpeed = ChongCiSpeed;
			break;
		default:
			GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
			break;
		}
	}
}

void AZhuJue_Character::EZhuangBeiWeapon()
{
	if (OverlapWeapon && !IsDeath())
	{
		if (ZhuangBeiWeapon)
		{
			ZhuangBeiWeapon->UnZhuangBei(this);
			OverlapWeapon->ZhuangBei(this);
		}
		else
		{
			OverlapWeapon->ZhuangBei(this);
		}
	}
	else
	{
		if (ZhuangBeiWeapon)
		{
			ZhuangBeiWeapon->UnZhuangBei(this);
		}
	}
}

void AZhuJue_Character::AttackDown()
{
	if (!IsDeath())
	{
		bAttackKeyDown = true;

		if (bYouWeapon)
		{
			Attack();
		}
	}
}

void AZhuJue_Character::Attack()
{
	if (!bIsAttack && !IsDeath())
	{
		UE_LOG(LogTemp, Warning, TEXT("bInterpToEnemy!!!"));
		bIsAttack = true;
		bInterpToEnemy = true;

		//通过AnimInstance来进行播放
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && AttackMontage)
		{
			float PlayRate = FMath::RandRange(1.25f, 1.75f);
			FString AnimName = FString::FromInt(FMath::RandRange(1, 2));
			//第一个参数，要播放哪一个蒙太奇，第二个是播放的速率
			AnimInstance->Montage_Play(AttackMontage, PlayRate);
			//跳转至某个指定片段，参数要跳转的片段名字，和这个片段在哪个蒙太奇里面
			AnimInstance->Montage_JumpToSection(FName(*AnimName), AttackMontage);
		}
	}
}

void AZhuJue_Character::AttackEnd()
{
	bIsAttack = false;
	bInterpToEnemy = false;

	if (bAttackKeyDown && !IsDeath())
	{
		AttackDown();
	}
}

void AZhuJue_Character::UpdateAttackTarget()
{
	TArray<AActor*> OverlappingActors;

	GetOverlappingActors(OverlappingActors, EnemyFilter);

	if (OverlappingActors.Num() == 0)
	{
		AttackTarget = nullptr;
		return;
	}

	AEnemy* MinEnemy = nullptr;
	float MinDistance = 1000.0f;
	const FVector Location = GetActorLocation();

	for (auto Actor : OverlappingActors)
	{
		AEnemy* Enemy = Cast<AEnemy>(Actor);
		if (Enemy && Enemy->EnemyStatus != EEnemyStatus::EES_Dead)
		{
			const float Distance = (Enemy->GetActorLocation() - Location).Size();
			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				MinEnemy = Enemy;
			}
		}
	}

	AttackTarget = MinEnemy;
}

void AZhuJue_Character::Die()
{
	SetZhuJueStatus(EZhuJueStatus::EZJS_Dead);
}

void AZhuJue_Character::DeathEnd()
{
	//停止动画
	GetMesh()->bPauseAnims = true;
	//没有骨架的更新
	GetMesh()->bNoSkeletonUpdate = true;

}

