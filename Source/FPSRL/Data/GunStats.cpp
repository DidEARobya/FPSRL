// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Data/GunStats.h"
#include "GunStats.h"

void UGunStats::InitStats(float fireRate, float shotChargeCost, float rechargeRate, float rechargeDelay)
{
	_fireRate = fireRate;
	_shotChargeCost = shotChargeCost;
	_rechargeRate = rechargeRate;
	_rechargeDelay = rechargeDelay;
}
void UGunStats::UpdateStats(UGunStats* toAdd)
{
	_fireRate += toAdd->GetFireRate();
	_shotChargeCost += toAdd->GetShotChargeCost();
	_rechargeRate += toAdd->GetRechargeRate();
	_rechargeDelay += toAdd->GetRechargeDelay();
}
float UGunStats::GetFireRate()
{
	return _fireRate;
}

float UGunStats::GetShotChargeCost()
{
	return _shotChargeCost;
}

float UGunStats::GetRechargeRate()
{
	return _rechargeRate;
}

float UGunStats::GetRechargeDelay()
{
	return _rechargeDelay;
}
