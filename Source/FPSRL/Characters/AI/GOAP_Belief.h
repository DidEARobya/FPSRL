// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FPSRL_API GOAP_Belief
{
public:
	GOAP_Belief(FString name);
	~GOAP_Belief();

	bool Evaluate();

	class FPSRL_API Builder
	{
		GOAP_Belief* belief;

	public:

		Builder(FString name)
		{
			belief = new GOAP_Belief(name);
		}

		Builder WithCondition(TFunction<bool()> condition)
		{
			belief->_condition = condition;
			return *this;
		}

		Builder WithLocation(FVector location)
		{
			belief->_location = location;
			return *this;
		}

		GOAP_Belief* Build()
		{
			return belief;
		}
	};

private:
	FString _name;
	TFunction<bool()> _condition;
	FVector _location;
};
