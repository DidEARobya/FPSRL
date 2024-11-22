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
	_agent->SetOwnerTarget(Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(_agent->_owner->GetWorld(), 0)));
}

void ChaseStrategy::Update(float deltaTime)
{
}

void ChaseStrategy::Stop()
{
	_agent->SetOwnerTarget(nullptr);
	_agent->isInTargetRange = true;
}

bool ChaseStrategy::Complete()
{
	FVector distance = _agent->_owner->GetActorLocation() - _agent->_target->GetActorLocation();
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Distance: %f"), distance.Length()));

	return (distance.Length() < 200);
}
