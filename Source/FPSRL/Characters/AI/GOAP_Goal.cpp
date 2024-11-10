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
