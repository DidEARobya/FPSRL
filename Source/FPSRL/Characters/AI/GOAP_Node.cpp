// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/AI/GOAP_Node.h"

GOAP_Node::GOAP_Node(GOAP_Node* nodeParent, GOAP_Action* nodeAction, TArray<GOAP_Belief*>* nodeEffects, int nodeCost)
{
	parent = nodeParent;
	action = nodeAction;
	requiredEffects = nodeEffects;
	neighbours = new TArray<GOAP_Node*>();
	cost = nodeCost;
}

GOAP_Node::~GOAP_Node()
{
}

bool GOAP_Node::IsDead()
{
	return (neighbours->Num() == 0 && action == nullptr);
}
