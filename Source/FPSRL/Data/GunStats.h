// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GunStats.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FPSRL_API UGunStats : public UObject
{
	GENERATED_BODY()
	
public:
	void InitStats(float fireRate, float shotChargeCost, float rechargeRate, float rechargeDelay);
	void UpdateStats(UGunStats* toAdd);

	float GetFireRate();
	float GetShotChargeCost();
	float GetRechargeRate();
	float GetRechargeDelay();
private: 
	UPROPERTY(EditAnywhere)
	float _fireRate = 0;
	UPROPERTY(EditAnywhere)
	float _shotChargeCost = 0;
	UPROPERTY(EditAnywhere)
	float _rechargeRate = 0;
	UPROPERTY(EditAnywhere)
	float _rechargeDelay = 0;
};
