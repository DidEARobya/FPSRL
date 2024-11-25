// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Components/GunArm.h"
#include "GunArm.h"
#include "DrawDebugHelpers.h"
#include "FPSRL/Upgrades/GunUpgradeModule.h"
#include "FPSRL/Data/GunStats.h"
#include "FPSRL/UI/PlayerHUD.h"
#include "FPSRL/Characters/Enemies/Enemy_Base.h"

// Sets default values for this component's properties
UGunArm::UGunArm()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_gunStats = CreateDefaultSubobject<UGunStats>(TEXT("Default Gun Stats"));
	checkf(_gunStats, TEXT("Gun Stats missing"));

	_cooldownTime = 0;
	_forceRecharge = false;
	_currentCharge = Gun_MaxCharge;
	// ...
}

void UGunArm::Fire(FVector target)
{
	if (_forceRecharge == true || _shotTimer < 1 / _fireRate)
	{
		return;
	}


	FVector start = GetComponentLocation();
	FVector end = ((target * 1000.0f) + start);

	DrawDebugLine(GetWorld(), start, end, FColor::Green, true);

	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_GameTraceChannel2, params))
	{
		if (hit.GetActor() == nullptr)
		{
			return;
		}

		if (AEnemy_Base* enemy = Cast<AEnemy_Base>(hit.GetActor()))
		{
			enemy->AdjustHealth(-10);
		}
	}

	_currentCharge -= _shotChargeCost;
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Current Charge: %f"), _currentCharge));
	onChargeUpdated.Execute(_currentCharge, Gun_MaxCharge);

	if (_currentCharge <= 0)
	{
		_forceRecharge = true;
	}

	_cooldownTime = 0;
	_shotTimer = 0;
}

void UGunArm::ApplyUpgrade(AGunUpgradeModule* upgrade)
{
	_gunStats->UpdateStats(upgrade->GetModuleStats());
	UpdateStats();
}

void UGunArm::BindOnChargeUpdated(UPlayerHUD* playerHUD)
{
	onChargeUpdated.BindUObject(playerHUD, &UPlayerHUD::SetGunCharge);
}

// Called when the game starts
void UGunArm::BeginPlay()
{
	Super::BeginPlay();

	UpdateStats();

	_shotTimer = 1 / _fireRate;
}

void UGunArm::UpdateStats()
{
	_fireRate = _gunStats->GetFireRate();
	_shotChargeCost = _gunStats->GetShotChargeCost();
	_rechargeRate = _gunStats->GetRechargeRate();
	_rechargeDelay = _gunStats->GetRechargeDelay();
}

// Called every frame
void UGunArm::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	_shotTimer += DeltaTime;
	_cooldownTime += DeltaTime;

	if (_cooldownTime >= _rechargeDelay)
	{
		_currentCharge = FMath::Clamp(_currentCharge + _rechargeRate * DeltaTime, 0.0f, Gun_MaxCharge);
		onChargeUpdated.Execute(_currentCharge, Gun_MaxCharge);

		if (_currentCharge >= Gun_MaxCharge)
		{
			_forceRecharge = false;
		}
	}
}

