// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/SkeletalMeshSocket.h"
#include "Characters/Player/ZhuJue_Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "CoreMinimal.h"
#include "GamePlay/JiaoHuXiTong.h"
#include "Weapon_Actor.generated.h"

UENUM(BlueprintType)
enum class EWeaponStatus : uint8
{
	EWS_ZhuangBei,
	EWS_Overlap
};

/**
 * 
 */
UCLASS()
class GETSTARTED_API AWeapon_Actor : public AJiaoHuXiTong
{
	GENERATED_BODY()

public:
	AWeapon_Actor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Sound") 
	USoundCue* ZhuangBeiCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Particle")
	bool bShouldWeaponParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	EWeaponStatus WeaponStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Attack")
	class UBoxComponent* AttackCollisionCmp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Attack")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Attack")
	TSubclassOf<UDamageType> DamageTypeClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Attack")
	class AController* WeaponOwner;

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	void ZhuangBei(AZhuJue_Character* ZhuJue);

	void UnZhuangBei(AZhuJue_Character* ZhuJue);

	UFUNCTION()
	virtual void OnAttackCollisionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnAttackCollisionOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void ActiveAttackCollision();

	UFUNCTION(BlueprintCallable)
	void DeactiveAttackCollision();
};
