// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class GOAP_Action;
class GOAP_Goal;
class GOAP_Plan;
class UGOAP_Agent;
class GOAP_Node;

class FPSRL_API GOAP_Planner
{
public:
	GOAP_Planner();
	~GOAP_Planner();

	GOAP_Plan* Plan(UGOAP_Agent* agent,TArray<GOAP_Goal*>* goals, GOAP_Goal* lastGoal);
	bool FindPath(GOAP_Node* parent,TArray<GOAP_Action*> actions);
};
