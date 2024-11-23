// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/AI/Strategies/PatrolStrategy.h"
#include "FPSRL/Characters/AI/GOAP_Agent.h"
#include "FPSRL/Characters/Enemies/Enemy_Base.h"
#include "NavigationSystem.h"

PatrolStrategy::PatrolStrategy(UGOAP_Agent* agent)
{
	_agent = agent;
}

PatrolStrategy::~PatrolStrategy()
{
}

void PatrolStrategy::Start()
{
	_navSystem = UNavigationSystemV1::GetNavigationSystem(_agent->_owner->GetWorld());
	_timer = 0;
	_delayBetweenPathing = _agent->patrolDelay;
}

void PatrolStrategy::Update(float deltaTime)
{
	if (_agent->HasPath() == true)
	{
		return;
	}

	_timer += deltaTime;

	if (_timer >= _delayBetweenPathing)
	{
		FNavLocation location;
		_navSystem->GetRandomPointInNavigableRadius(_agent->_owner->GetActorLocation(), _agent->patrolRadius, location);

		_agent->SetDestination(location);
		_timer = 0;
	}
}

void PatrolStrategy::Stop()
{
	_timer = 0;
	_agent->SetDestination(_agent->_owner->GetActorLocation());
}

bool PatrolStrategy::Complete()
{
	return (_agent->_isInTargetRange == true || _agent->_hasLineOfSight == true);
}
