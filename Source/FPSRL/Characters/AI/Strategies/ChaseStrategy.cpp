// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/AI/Strategies/ChaseStrategy.h"
#include "FPSRL/Characters/AI/GOAP_Agent.h"
#include "FPSRL/Characters/Enemies/Enemy_Base.h"
#include "FPSRL/Characters/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

ChaseStrategy::ChaseStrategy(UGOAP_Agent* agent)
{
	_agent = agent;
}

ChaseStrategy::~ChaseStrategy()
{
}

void ChaseStrategy::Start()
{
}

void ChaseStrategy::Update(float deltaTime)
{
	_agent->SetDestination(_agent->_player->GetActorLocation());
}

void ChaseStrategy::Stop()
{
	_agent->_owner->GetController()->StopMovement();
}

bool ChaseStrategy::Complete()
{
	return (_agent->_isInTargetRange == true || _agent->_hasLineOfSight == false);
}
