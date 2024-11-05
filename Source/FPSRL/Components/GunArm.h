// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GunArm.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSRL_API UGunArm : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunArm();
	void Fire(FVector target);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float _fireRate;
	float _shotTimer;

	UPROPERTY(EditAnywhere)
	float _shotChargeCost;

	UPROPERTY(EditAnywhere)
	float _maxCharge;
	float _currentCharge;
	UPROPERTY(EditAnywhere)
	float _rechargeRate;

	UPROPERTY(EditAnywhere)
	float _timeToStartRecharge;
	float _cooldownTime;

	bool _forceRecharge;
};
