// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FuDongPingTai.generated.h"

UCLASS()
class GETSTARTED_API AFuDongPingTai : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuDongPingTai();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* PingTaiMeshCmp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh|YiDong")
	FVector StartPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh|YiDong", meta = (MakeEditWidget = "true"))
	FVector EndPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh|YiDong")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh|YiDong")
	float TingLiuTime;

	bool bIsTingLiu;

	FTimerHandle TingLiuTimerHandle;

	float JuLi;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
