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
}

void AttackStrategy::Update(float deltaTime)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Attacking")));
}

void AttackStrategy::Stop()
{
	_agent->isInTargetRange = false;
}

bool AttackStrategy::Complete()
{
	FVector distance = _agent->_owner->GetActorLocation() - _agent->_target->GetActorLocation();

	return (distance.Length() > 200);
}
