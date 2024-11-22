// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/AI/BeliefFactory.h"
#include "FPSRL/Characters/AI/GOAP_Belief.h"

BeliefFactory::BeliefFactory(TMap<FString, GOAP_Belief*> *beliefs)
{
	_beliefs = beliefs;
}

BeliefFactory::~BeliefFactory()
{
}

void BeliefFactory::AddBelief(FString name, TFunction<bool()> condition)
{
	_beliefs->Add(name, GOAP_Belief::Builder(name).WithCondition(condition).Build());
}

void BeliefFactory::AddLocationBelief(FString name, FVector location)
{
	_beliefs->Add(name, GOAP_Belief::Builder(name).WithLocation(location).Build());
}
