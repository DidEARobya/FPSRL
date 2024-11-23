// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSRL/Interfaces/ActionStrategy.h"

class UGOAP_Agent;
class UNavigationSystemV1;
class FPSRL_API PatrolStrategy : public IActionStrategy
{
public:
	PatrolStrategy(UGOAP_Agent* agent);
	~PatrolStrategy();

	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Stop() override;

	virtual bool Complete() override;
private:

	UGOAP_Agent* _agent;
	UNavigationSystemV1* _navSystem;

	float _timer;
	float _delayBetweenPathing;
};
