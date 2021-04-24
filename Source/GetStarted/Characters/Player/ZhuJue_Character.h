// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimMontage.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZhuJue_Character.generated.h"

UENUM(BlueprintType)
enum class EZhuJueStatus : uint8
{
	EZJS_Normal,
	EZJS_ChongCi,
	EZJS_Dead
};

UENUM(BlueprintType)
enum class ENaiLiStatus : uint8
{
	ENLS_Normal,
	ENLS_WuNaiLi,
	ENLS_NaiLiHuiFu
};

UCLASS()
class GETSTARTED_API AZhuJue_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZhuJue_Character();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmCmp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraCmp;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ZhuJue|ShuZhi")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZhuJue|ShuZhi")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ZhuJue|ShuZhi")
	float MaxNaiLi;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZhuJue|ShuZhi")
	float NaiLi;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZhuJue|ShuZhi")
	int Coins;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ZhuJue|Speed")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ZhuJue|Speed")
	float ChongCiSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZhuJue|Speed")
	float NaiLiXiaoHao;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZhuJue|Speed")
	float NaiLiPiLaoRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZhuJue|Speed")
	EZhuJueStatus ZhuJueStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZhuJue|Speed")
	ENaiLiStatus NaiLiStatus;

	bool bOnShift;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ZhuJue|Weapon")
	bool bYouWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ZhuJue|Weapon")
	class AWeapon_Actor* ZhuangBeiWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ZhuJue|Weapon")
	AWeapon_Actor* OverlapWeapon;

	bool bAttackKeyDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ZhuJue|Anim")
	bool bIsAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ZhuJue|Anim")
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ZhuJue|Attack")
	class AEnemy* AttackTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZhuJue|Attack")
	TSubclassOf<AEnemy> EnemyFilter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZhuJue|Attack")
	float InterpSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ZhuJue|Attack")
	bool bInterpToEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZhuJue|Hit")
	class UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZhuJue|Hit")
	class USoundCue* HitSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;

	void Move_QianHou(float value);
	void Move_ZuoYou(float value);
	void Look_ShangXia(float value);
	void Look_ZuoYou(float value);

	UFUNCTION(BlueprintCallable)
	void AddHealth(float value);

	UFUNCTION(BlueprintCallable)
	void AddNaiLi(float value);

	UFUNCTION(BlueprintCallable)
	void AddCoin(int value);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	FORCEINLINE void OnShiftDown() { bOnShift = true; }

	FORCEINLINE void OnShiftUp() { bOnShift = false; }

	void SetZhuJueStatus(EZhuJueStatus status);

	void EZhuangBeiWeapon();

	void AttackDown();

	FORCEINLINE void AttackUp() { bAttackKeyDown = false; }

	void Attack();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	void UpdateAttackTarget();

	void Die();

	UFUNCTION(BlueprintCallable)
	void DeathEnd();

	FORCEINLINE bool IsDeath() { return ZhuJueStatus == EZhuJueStatus::EZJS_Dead; }

};
