// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSRL/Interfaces/ActionStrategy.h"

class UGOAP_Agent;

class FPSRL_API ChaseStrategy : public IActionStrategy
{
public:
	ChaseStrategy(UGOAP_Agent* agent);
	~ChaseStrategy();

	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Stop() override;

	virtual bool Complete() override;
private:

	UGOAP_Agent* _agent;
};
