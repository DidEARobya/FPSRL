// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UProgressBar;

UCLASS()
class FPSRL_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetGunCharge(float currentCharge);
	void SetGunMaxCharge(float maxCharge);

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* _gunChargeBar;

	float _gunMaxCharge;
	float _displayGunCharge = 100;
	float _targetCharge = 100;
	float _deltaTime;
};
