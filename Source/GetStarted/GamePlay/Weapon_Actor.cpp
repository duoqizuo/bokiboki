// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/Weapon_Actor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Controller.h"
#include "Characters/Enemys/Enemy.h"

AWeapon_Actor::AWeapon_Actor()
{
	ChuFaSphereCmp->SetSphereRadius(64.0f);

	DisPlayMeshCmp->DestroyComponent(); //销毁组件
	//然后重新创建,需要更改标识符
	DisPlayMeshCmp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshMeshCmp"));
	DisPlayMeshCmp->SetupAttachment(GetRootComponent());

	AttackCollisionCmp = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollisionCmp"));
	AttackCollisionCmp->SetupAttachment(DisPlayMeshCmp, "WeaponSocket");

	DeactiveAttackCollision();

	bShouldWeaponParticle = true;

	WeaponStatus = EWeaponStatus::EWS_Overlap;

	Damage = 25.0f;

}

void AWeapon_Actor::BeginPlay()
{
	Super::BeginPlay();

	AttackCollisionCmp->OnComponentBeginOverlap.AddDynamic(this, &AWeapon_Actor::OnAttackCollisionOverlapBegin);
	AttackCollisionCmp->OnComponentEndOverlap.AddDynamic(this, &AWeapon_Actor::OnAttackCollisionOverlapEnd);
}

void AWeapon_Actor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor && WeaponStatus == EWeaponStatus::EWS_Overlap)
	{
		AZhuJue_Character* ZhuJue = Cast<AZhuJue_Character>(OtherActor);
		if (ZhuJue)
		{
			ZhuJue->OverlapWeapon = this;
		}
	}
}

void AWeapon_Actor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	if (OtherActor)
	{
		AZhuJue_Character* ZhuJue = Cast<AZhuJue_Character>(OtherActor);
		if (ZhuJue && ZhuJue->OverlapWeapon == this)
		{
			ZhuJue->OverlapWeapon = nullptr;
		}
	}
}

void AWeapon_Actor::ZhuangBei(AZhuJue_Character* ZhuJue)
{
	if (ZhuJue)
	{
		WeaponStatus = EWeaponStatus::EWS_ZhuangBei;
		const USkeletalMeshSocket* RightHandSocket = ZhuJue->GetMesh()->GetSocketByName("RightHandWeapon");
		if (RightHandSocket)
		{
			RightHandSocket->AttachActor(this, ZhuJue->GetMesh());
			ZhuJue->bYouWeapon = true;
			ZhuJue->ZhuangBeiWeapon = this;
			ZhuJue->OverlapWeapon = nullptr;

			bNeedRotator = false;
			if (ZhuangBeiCue)
			{
				UGameplayStatics::PlaySoundAtLocation(this, ZhuangBeiCue, GetActorLocation());
			}
			if (!bShouldWeaponParticle)
			{
				IdleParticleCmp->Deactivate();
			}
		}
	}
}

void AWeapon_Actor::UnZhuangBei(AZhuJue_Character* ZhuJue)
{
	if (ZhuJue && !(ZhuJue->bIsAttack))
	{
		WeaponStatus = EWeaponStatus::EWS_Overlap;

		ZhuJue->bYouWeapon = false;
		ZhuJue->ZhuangBeiWeapon = nullptr;
		if (ZhuJue->OverlapWeapon == nullptr)
		{
			ZhuJue->OverlapWeapon = this;
		}

		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		SetActorRotation(FRotator(0.0f));
		SetActorScale3D(FVector(1.0f));

		bNeedRotator = true;

		if (bShouldWeaponParticle)
		{
			IdleParticleCmp->Activate();
		}
	}
}

void AWeapon_Actor::OnAttackCollisionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AEnemy* Enemy = Cast<AEnemy>(OtherActor);
		if (Enemy)
		{
			if (Enemy->HitParticle)
			{
				const USkeletalMeshSocket* WeaponSocket = ((USkeletalMeshComponent*)DisPlayMeshCmp)->GetSocketByName("WeaponSocket");
				if (WeaponSocket)
				{
					FVector SocketLocation = WeaponSocket->GetSocketLocation((USkeletalMeshComponent*)DisPlayMeshCmp);
					UGameplayStatics::SpawnEmitterAtLocation(this, Enemy->HitParticle, SocketLocation, FRotator(0.0f), true);
				}
			}
			if (Enemy->HitSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, Enemy->HitSound, Enemy->GetActorLocation());
			}
			if (DamageTypeClass)
			{
				UGameplayStatics::ApplyDamage(Enemy, Damage, WeaponOwner, this, DamageTypeClass);
			}
		}
	}
}

void AWeapon_Actor::OnAttackCollisionOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AWeapon_Actor::ActiveAttackCollision()
{
	AttackCollisionCmp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackCollisionCmp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	AttackCollisionCmp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AttackCollisionCmp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AWeapon_Actor::DeactiveAttackCollision()
{
	AttackCollisionCmp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
