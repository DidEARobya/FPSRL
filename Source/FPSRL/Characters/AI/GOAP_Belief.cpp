// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/AI/GOAP_Belief.h"

GOAP_Belief::GOAP_Belief(FString name)
{
	_name = name;
}

GOAP_Belief::~GOAP_Belief()
{
}

bool GOAP_Belief::Evaluate()
{
	return _condition();
}
