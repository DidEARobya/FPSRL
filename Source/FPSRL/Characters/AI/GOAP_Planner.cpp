// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/AI/GOAP_Planner.h"
#include "FPSRL/Characters/AI/GOAP_Goal.h"
#include "FPSRL/Characters/AI/GOAP_Action.h"
#include "FPSRL/Characters/AI/GOAP_Belief.h"
#include "FPSRL/Characters/AI/GOAP_Node.h"
#include "FPSRL/Characters/AI/GOAP_Agent.h"
#include "FPSRL/Characters/AI/GOAP_Plan.h"

GOAP_Planner::GOAP_Planner()
{
	/**/
}

GOAP_Planner::~GOAP_Planner()
{
}

GOAP_Plan* GOAP_Planner::Plan(UGOAP_Agent* agent, TArray<GOAP_Goal*>* goals, GOAP_Goal* lastGoal)
{
	TArray<GOAP_Goal*> orderedGoals = goals->FilterByPredicate([&](const GOAP_Goal* index) { return !(const_cast<GOAP_Goal*>(index)->CheckIfFulfilled()); });

	if (lastGoal == nullptr)
	{
		orderedGoals.Sort([](const GOAP_Goal& A, const GOAP_Goal& B) { return &A._priority < &B._priority; });
	}
	else
	{
		orderedGoals.Sort([lastGoal](const GOAP_Goal& A, const GOAP_Goal& B) { return (&A == const_cast<GOAP_Goal*>(lastGoal)) ? &A._priority < &B._priority - 1 : &A._priority < &B._priority; });
	}

	for (GOAP_Goal* goal : orderedGoals)
	{
		GOAP_Node* goalNode = new GOAP_Node(nullptr, nullptr, &goal->_desiredEffects, 0);

		if (FindPath(goalNode, *agent->_actions) == true)
		{
			if (goalNode->IsDead() == true)
			{
				continue;
			}

			TArray<GOAP_Action*>* actionStack = new TArray<GOAP_Action*>();

			while (goalNode->neighbours->Num() > 0)
			{
				goalNode->neighbours->Sort([](const GOAP_Node& a, const GOAP_Node& b) { return a.cost < b.cost; });
				GOAP_Node* cheapestNeighbour = goalNode->neighbours->Pop();

				goalNode = cheapestNeighbour;
				actionStack->Push(cheapestNeighbour->action);
			}

			return new GOAP_Plan(goal, actionStack, goalNode->cost);
		}
	}

	return nullptr;
}

bool GOAP_Planner::FindPath(GOAP_Node* parent, TArray<GOAP_Action*> actions)
{
	actions.Sort([](const GOAP_Action& a, const GOAP_Action& b) { return a._cost < b._cost; });

	for (GOAP_Action* action : actions)
	{
		TArray<GOAP_Belief*> requiredEffects = *parent->requiredEffects;

		requiredEffects.RemoveAll([&](const GOAP_Belief* index) { return const_cast<GOAP_Belief*>(index)->Evaluate(); });

		if (requiredEffects.Num() == 0)
		{
			return true;
		}

		if (action->_effects.Contains(*requiredEffects.CreateIterator()) == true)
		{
			TArray<GOAP_Belief*>* newRequiredEffects = new TArray<GOAP_Belief*>(requiredEffects);
			newRequiredEffects->RemoveAll([&](const GOAP_Belief* index) { return action->_effects.Contains(index); });

			for (GOAP_Belief* belief : action->_preconditions)
			{
				if (newRequiredEffects->Contains(belief) == false)
				{
					newRequiredEffects->Add(belief);
				}
			}

			TArray<GOAP_Action*> newAvailableActions = TArray<GOAP_Action*>(actions);
			newAvailableActions.Remove(action);

			GOAP_Node* newNode = new GOAP_Node(parent, action, newRequiredEffects, parent->cost + action->_cost);

			if (FindPath(newNode, newAvailableActions) == true)
			{
				parent->neighbours->Add(newNode);
				newRequiredEffects->RemoveAll([&](const GOAP_Belief* index) { return newNode->action->_preconditions.Contains(index); });
			}

			if (newRequiredEffects->Num() == 0)
			{
				return true;
			}
		}
	}

	return false;
}
