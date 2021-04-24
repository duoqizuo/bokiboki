// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TimerManager.h"
#include "Characters/Player/ZhuJue_Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JiGuanMen_Actor.generated.h"

UCLASS()
class GETSTARTED_API AJiGuanMen_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJiGuanMen_Actor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DoorMesh")
	UBoxComponent* JiGuanBoxCmp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DoorMesh")
	UStaticMeshComponent* DoorMeshCmp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DoorMesh")
	UStaticMeshComponent* JiGuanMeshCmp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JiGuanDoor|JiGuan")
	FVector InitJiGuanLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JiGuanDoor|Door")
	FVector InitDoorLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JiGuanDoor|Door")
	float YanShiTime;

	FTimerHandle JiGuanMenTimeHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnJiGuanBeginBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnJiGuanEndBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "JiGuanDoor|JiGuan")
	void CaiXiaJiGuan();

	UFUNCTION(BlueprintImplementableEvent, Category = "JiGuanDoor|JiGuan")
	void LiKaiJiGuan();

	UFUNCTION(BlueprintImplementableEvent, Category = "JiGuanDoor|Door")
	void OpenDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "JiGuanDoor|Door")
	void CloseDoor();

	UFUNCTION(BlueprintCallable, Category = "JiGuanDoor|JiGuan")
	void UpdateJiGuanLocation(FVector offset);

	UFUNCTION(BlueprintCallable, Category = "JiGuanDoor|Door")
	void UpdateDoorLocation(FVector offset);

};
