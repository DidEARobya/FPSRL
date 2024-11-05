// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Components/GunArm.h"
#include "GunArm.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGunArm::UGunArm()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_cooldownTime = 0;
	_forceRecharge = false;
	// ...
}

void UGunArm::Fire(FVector target)
{
	if (_forceRecharge == true || _shotTimer < 1 / _fireRate)
	{
		return;
	}

	FHitResult outHit;
	FVector start = GetComponentLocation();

	FVector end = ((target * 1000.0f) + start);

	FCollisionQueryParams collisionParams;

	DrawDebugLine(GetWorld(), start, end, FColor::Green, true);

	//bool isHit = GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, collisionParams);

	//if (isHit == true)
	//{
	//	if (outHit.bBlockingHit == true)
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Hit: %s"), *outHit.GetActor()->GetName()));
	//	}
	//}

	_currentCharge -= _shotChargeCost;
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Current Charge: %f"), _currentCharge));

	if (_currentCharge <= 0)
	{
		_forceRecharge = true;
	}

	_cooldownTime = 0;
	_shotTimer = 0;
}

// Called when the game starts
void UGunArm::BeginPlay()
{
	Super::BeginPlay();

	_currentCharge = _maxCharge;
	_shotTimer = 1 / _fireRate;
}

// Called every frame
void UGunArm::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	_shotTimer += DeltaTime;
	_cooldownTime += DeltaTime;

	if (_cooldownTime >= _timeToStartRecharge)
	{
		_currentCharge = FMath::Clamp(_currentCharge + _rechargeRate * DeltaTime, 0.0f, _maxCharge);

		if (_currentCharge >= _maxCharge)
		{
			_forceRecharge = false;
		}
	}
}

