// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class GOAP_Action;
class GOAP_Goal;

class FPSRL_API GOAP_Planner
{
public:
	GOAP_Planner(/*agent,*/ TArray<GOAP_Goal> goals, GOAP_Goal lastGoal);
	~GOAP_Planner();

	bool FindPath(/*Node,*/ TArray<GOAP_Action> actions);
};
