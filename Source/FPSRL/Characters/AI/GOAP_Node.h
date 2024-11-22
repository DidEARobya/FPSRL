// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class GOAP_Action;
class GOAP_Belief;

class FPSRL_API GOAP_Node
{
public:
	GOAP_Node(GOAP_Node* nodeParent, GOAP_Action* nodeAction, TArray<GOAP_Belief*>* nodeEffects, int nodeCost);
	~GOAP_Node();

	bool IsDead();
public:

	GOAP_Node* parent;
	GOAP_Action* action;
	TArray<GOAP_Belief*>* requiredEffects;
	TArray<GOAP_Node*>* neighbours;
	int cost;
};
