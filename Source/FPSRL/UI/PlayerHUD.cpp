// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/UI/PlayerHUD.h"
#include "Components/ProgressBar.h"
#include "FPSRL/Components/GunArm.h"

void UPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateHealthBar(InDeltaTime);
	UpdateChargeBar(InDeltaTime);
}
void UPlayerHUD::UpdateHealthBar(float deltaTime)
{
	_displayHealth = FMath::Lerp(_displayHealth, _targetHealth, 0.1f);
	_healthBar->SetPercent(_displayHealth / _maxHealth);
}
void UPlayerHUD::SetHealth(float currentHealth, float maxHealth)
{
	_targetHealth = currentHealth;
	_maxHealth = maxHealth;
}
void UPlayerHUD::UpdateChargeBar(float deltaTime)
{
	if (_displayGunCharge > _targetCharge)
	{
		_displayGunCharge = FMath::Lerp(_displayGunCharge, _targetCharge, 0.1f);
	}
	else
	{
		_displayGunCharge = FMath::FInterpConstantTo(_displayGunCharge, _targetCharge, deltaTime, 10);
	}

	_gunChargeBar->SetPercent(_displayGunCharge / _gunMaxCharge);
}
void UPlayerHUD::SetGunCharge(float currentCharge, float maxCharge)
{
	_targetCharge = currentCharge;
	_gunMaxCharge = maxCharge;
}
