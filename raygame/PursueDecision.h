#pragma once
#include "ABDecision.h"

class PursueDecision : public ABDecision
{
public:
	using ABDecision::ABDecision;

	//Decides what happens when a decision is made
	void makeDecision(Agent* agent, float deltaTime) override;

};