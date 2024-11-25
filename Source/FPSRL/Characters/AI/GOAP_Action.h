// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSRL/Interfaces/ActionStrategy.h"

class GOAP_Belief;
class Strategy_Base;

class FPSRL_API GOAP_Action
{
public:
	GOAP_Action(FString name);
	~GOAP_Action();

	void Start(); //Start Strategy
	void Update(float deltaTime); //Evaluate Strategy and Beliefs
	void Stop(); //Stop Strategy

	bool IsComplete();

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
		Builder WithStrategy(IActionStrategy* strategy)
		{
			action->_strategy = strategy;
			return *this;
		}
		Builder AddPrecondition(GOAP_Belief* precondition)
		{
			action->_preconditions.Add(precondition);
			return *this;
		}
		Builder AddEffect(GOAP_Belief* effect)
		{
			action->_effects.Add(effect);
			return *this;
		}
		GOAP_Action* Build()
		{
			return action;
		}
	};

public:

	IActionStrategy* _strategy;

	TArray<GOAP_Belief*> _preconditions;
	TArray<GOAP_Belief*> _effects;

	FString _name;
	int _cost;
};
