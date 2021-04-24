// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/ShiQuWu.h"

AShiQuWu::AShiQuWu()
{
	ChuFaSphereCmp->SetSphereRadius(50.0f);
}

void AShiQuWu::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor)
	{
		AZhuJue_Character* ZhuJue = Cast<AZhuJue_Character>(OtherActor);
		if (ZhuJue)
		{
			if (OverlapParticle)
			{
				UGameplayStatics::SpawnEmitterAtLocation(this, OverlapParticle, GetActorLocation(), FRotator::ZeroRotator, true);
			}
			if (OverlapSoundCue)
			{
				UGameplayStatics::PlaySoundAtLocation(this, OverlapSoundCue, GetActorLocation());
			}
			ShiQu(ZhuJue);
			Destroy();
		}
	}
}

void AShiQuWu::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

}
