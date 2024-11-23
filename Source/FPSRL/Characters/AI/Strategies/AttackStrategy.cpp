// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/AI/Strategies/AttackStrategy.h"
#include "FPSRL/Characters/AI/GOAP_Agent.h"
#include "FPSRL/Characters/Enemies/Enemy_Base.h"
#include "FPSRL/Characters/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

AttackStrategy::AttackStrategy(UGOAP_Agent* agent)
{
	_agent = agent;
}

AttackStrategy::~AttackStrategy()
{
}

void AttackStrategy::Start()
{
	_agent->_isAttacking = true;
	_agent->_isInTargetRange = true;
}

void AttackStrategy::Update(float deltaTime)
{
}

void AttackStrategy::Stop()
{
	_agent->_isAttacking = false;
}

bool AttackStrategy::Complete()
{
	return !_agent->_isInTargetRange;
}
