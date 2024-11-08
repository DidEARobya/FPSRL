// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/UI/PlayerHUD.h"
#include "Components/ProgressBar.h"
#include "FPSRL/Components/GunArm.h"

void UPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (_displayGunCharge > _targetCharge)
	{
		_displayGunCharge = FMath::Lerp(_displayGunCharge, _targetCharge, 0.1f);
	}
	else
	{
		_displayGunCharge = FMath::FInterpConstantTo(_displayGunCharge, _targetCharge, InDeltaTime, 10);
	}
	
	_gunChargeBar->SetPercent(_displayGunCharge / _gunMaxCharge);
}
void UPlayerHUD::SetGunCharge(float currentCharge)
{
	_targetCharge = currentCharge;
}

void UPlayerHUD::SetGunMaxCharge(float maxCharge)
{
	_gunMaxCharge = maxCharge;
}
