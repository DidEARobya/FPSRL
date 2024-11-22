// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/AI/GOAP_Action.h"

GOAP_Action::GOAP_Action(FString name)
{
	_name = name;
	_preconditions = *new TArray<GOAP_Belief*>();
	_effects = *new TArray<GOAP_Belief*>();
}

GOAP_Action::~GOAP_Action()
{
}

void GOAP_Action::Start()
{
	_strategy->Start();
}

void GOAP_Action::Update(float deltaTime)
{
	_strategy->Update(deltaTime);
}

void GOAP_Action::Stop()
{
	_strategy->Stop();
}

bool GOAP_Action::IsComplete()
{
	return _strategy->Complete();
}
