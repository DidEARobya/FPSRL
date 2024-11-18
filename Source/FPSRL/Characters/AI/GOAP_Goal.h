// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class GOAP_Belief;
class FPSRL_API GOAP_Goal
{
public:
	GOAP_Goal(FString name);
	~GOAP_Goal();

	bool CheckIfFulfilled();

	class FPSRL_API Builder
	{
		GOAP_Goal* goal;

	public:
		Builder(FString name)
		{
			goal = new GOAP_Goal(name);
		}
		Builder* WithPriority(int priority)
		{
			goal->_priority = priority;
			return this;
		}
		Builder* AddDesiredEffect(GOAP_Belief* effect)
		{
			goal->_desiredEffects.Add(effect);
			return this;
		}
		GOAP_Goal* Build()
		{
			return goal;
		}
	};

public:
	FString _name;
	int _priority;

	TArray<GOAP_Belief*> _desiredEffects;
};
