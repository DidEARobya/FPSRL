// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/AI/GOAP_Plan.h"

GOAP_Plan::GOAP_Plan(GOAP_Goal* planGoal, TArray<GOAP_Action*>* planActions, int planCost)
{
	goal = planGoal;
	actions = planActions;
	cost = planCost;
}

GOAP_Plan::~GOAP_Plan()
{
}
