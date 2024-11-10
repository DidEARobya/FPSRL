// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class GOAP_Belief;

class FPSRL_API GOAP_Action
{
public:
	GOAP_Action(FString name);
	~GOAP_Action();

	void Start(); //Start Strategy
	void Update(float deltaTime); //Evaluate Strategy and Beliefs
	void Stop(); //Stop Strategy

	class FPSRL_API Builder
	{
		GOAP_Action* action;

	public:

		Builder(FString name)
		{
			action = new GOAP_Action(name);
		}

		Builder WithCost(int cost)
		{
			action->_cost = cost;
			return *this;
		}
		Builder AddPrecondition(GOAP_Belief* precondition)
		{
			action->_preconditions.Add(precondition);
		}
		Builder AddEffect(GOAP_Belief* effect)
		{
			action->_effects.Add(effect);
		}
		GOAP_Action* Build()
		{
			return action;
		}
	};

private:
	TArray<GOAP_Belief*> _preconditions;
	TArray<GOAP_Belief*> _effects;

	FString _name;
	int _cost;
};
