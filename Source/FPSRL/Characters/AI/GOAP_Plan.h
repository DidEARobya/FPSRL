// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class GOAP_Goal;
class GOAP_Action;

class FPSRL_API GOAP_Plan
{
public:
	GOAP_Plan(GOAP_Goal* planGoal, TArray<GOAP_Action*>* planActions, int planCost);
	~GOAP_Plan();

public:
	GOAP_Goal* goal;
	TArray<GOAP_Action*>* actions;
	int cost;
};
