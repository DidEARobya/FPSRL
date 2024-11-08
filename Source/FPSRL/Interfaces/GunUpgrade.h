// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GunUpgrade.generated.h"

class UGunStats;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UGunUpgrade : public UInterface
{
	GENERATED_BODY()
};

class FPSRL_API IGunUpgrade
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UGunStats* GetUpgradeStats();

protected:
	UGunStats* _upgradeStats;
};
