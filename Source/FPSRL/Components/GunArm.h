// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GunArm.generated.h"

class AGunUpgradeModule;
class UGunStats;
class UPlayerHUD;

DECLARE_DELEGATE_OneParam(FOnChargeUpdated, float);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSRL_API UGunArm : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunArm();
	void Fire(FVector target);
	void ApplyUpgrade(AGunUpgradeModule* upgrade);

	void BindOnChargeUpdated(UPlayerHUD* playerHUD);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void UpdateStats();

public:
	const float Gun_MaxCharge = 100;
private:
	FOnChargeUpdated onChargeUpdated;

	UPROPERTY(EditAnywhere)
	UGunStats* _gunStats;

	float _fireRate;
	float _shotChargeCost;
	float _rechargeRate;
	float _rechargeDelay;

	float _shotTimer;
	float _currentCharge;
	float _cooldownTime;

	bool _forceRecharge;
};
