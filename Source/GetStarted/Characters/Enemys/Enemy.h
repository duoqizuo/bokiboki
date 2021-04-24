// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UENUM(BlueprintType)
enum class EEnemyStatus : uint8
{
	EES_Idle,
	EES_Chase,
	EES_Attack,
	EES_Dead
};

UCLASS()
class GETSTARTED_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemys|Mesh")
	class USphereComponent* ChaseVolumeCmp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemys|Mesh")
	USphereComponent* AttackVolumeCmp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemys|Status")
	EEnemyStatus EnemyStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemys|AI")
	class AAIController* AIController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemys|Attack")
	bool bIsAttackVolume;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemys|Attack")
	class UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemys|Attack")
	float InterpSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemys|Attack")
	bool bInterpToPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Status")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Status")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Status")
	class UWidgetComponent* HealthBarWidgetCmp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Status")
	class UProgressBar* HealthBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Attack")
	class UBoxComponent* LeftAttackSocketCmp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Attack")
	UBoxComponent* RightAttackSocketCmp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Attack")
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Attack")
	TSubclassOf<UDamageType> DamageTypeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Hit")
	class UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Hit")
	class USoundCue* HitSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void OnChaseVolumeOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnChaseVolumeOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	virtual void OnAttackVolumeOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnAttackVolumeOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void ChasePlayer(class AZhuJue_Character* TargetPlayer);

	void Attack();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UFUNCTION()
	virtual void OnLeftAttackOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnLeftAttackOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void OnRightAttackOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnRightAttackOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void ActiveLeftAttackCollision();

	UFUNCTION(BlueprintCallable)
	void DeactiveLeftAttackCollision();

	UFUNCTION(BlueprintCallable)
	void ActiveRightAttackCollision();

	UFUNCTION(BlueprintCallable)
	void DeactiveRightAttackCollision();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Die();

	UFUNCTION(BlueprintCallable)
	void DeathEnd();

	FORCEINLINE bool IsDeath() { return EnemyStatus == EEnemyStatus::EES_Dead; }

	bool IsTarget();

};
