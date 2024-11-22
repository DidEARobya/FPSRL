// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Interfaces/GunUpgrade.h"
#include "FPSRL/Data/GunStats.h"

// Add default functionality here for any IGunUpgrade functions that are not pure virtual.

UGunStats* IGunUpgrade::GetUpgradeStats()
{
	return _upgradeStats;
}
