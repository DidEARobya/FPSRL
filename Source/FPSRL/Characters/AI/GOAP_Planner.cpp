// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/AI/GOAP_Planner.h"
#include "FPSRL/Characters/AI/GOAP_Goal.h"
#include "FPSRL/Characters/AI/GOAP_Action.h"
#include "FPSRL/Characters/AI/GOAP_Belief.h"

GOAP_Planner::GOAP_Planner(/*agent,*/ TArray<GOAP_Goal> goals, GOAP_Goal lastGoal)
{
	TArray<GOAP_Goal> orderedGoals;

	for (GOAP_Goal goal : goals)
	{
		if (goal.CheckIfFulfilled() == false)
		{
			orderedGoals.Add(goal);
		}
	}

	orderedGoals.Sort([lastGoal](const GOAP_Goal& A, const GOAP_Goal& B) { return (&A == const_cast<GOAP_Goal*>(&lastGoal)) ? &B._priority < &A._priority - 1 : &B._priority < &A._priority; });
}

GOAP_Planner::~GOAP_Planner()
{
}

bool GOAP_Planner::FindPath(TArray<GOAP_Action> actions)
{
	return false;
}
