// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShengChengSpace.generated.h"

UCLASS()
class GETSTARTED_API AShengChengSpace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShengChengSpace();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Box")
	UBoxComponent* ShengChengBoxCmp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Box|ShengCheng")
	TArray<TSubclassOf<AActor>> ActorClassesArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Box|ShengCheng")
	FVector GetShengChengWeiZhi();

	UFUNCTION(BlueprintPure, Category = "Box|ShengCheng")
	TSubclassOf<AActor> GetActorClass();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Box|ShengCheng")
	void ShengChengActor(UClass* ActorClass, FVector ActorLocation);

};
