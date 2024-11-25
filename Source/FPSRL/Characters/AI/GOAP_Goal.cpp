// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/AI/GOAP_Goal.h"
#include "FPSRL/Characters/AI/GOAP_Belief.h"

GOAP_Goal::GOAP_Goal(FString name)
{
	_name = name;
	_desiredEffects = *new TArray<GOAP_Belief*>();
}

GOAP_Goal::~GOAP_Goal()
{
}

bool GOAP_Goal::CheckIfFulfilled()
{
	if (_desiredEffects.Num() == 0)
	{
		return true;
	}

	for (GOAP_Belief* belief : _desiredEffects)
	{
		if (belief->Evaluate() == false)
		{
			return false;
		}
	}

	return true;
}
