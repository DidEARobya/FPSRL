// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class GOAP_Belief;

class FPSRL_API BeliefFactory
{
public:
	BeliefFactory(/*Agent, */TMap<FString, GOAP_Belief*> beliefs);
	~BeliefFactory();

	void AddBelief(FString name, TFunction<bool()> condition);
	void AddLocationBelief(FString name, FVector location);
private:
	//Agent
	TMap<FString, GOAP_Belief*> _beliefs;
};
