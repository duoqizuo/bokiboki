// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JiaoHuXiTong.generated.h"

UCLASS()
class GETSTARTED_API AJiaoHuXiTong : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJiaoHuXiTong();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* ChuFaSphereCmp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMeshComponent* DisPlayMeshCmp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* IdleParticleCmp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JiaoHu|Particle")
	UParticleSystem* OverlapParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JiaoHu|Sound")
	USoundCue* OverlapSoundCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JiaoHu|XuanZhuan")
	bool bNeedRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JiaoHu|XuanZhuan")
	float RotatorSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
