#pragma once
#include "SteeringBehaviour.h"

class Actor;

class WanderBehaviour : public SteeringBehaviour
{
public:
	WanderBehaviour();
	WanderBehaviour(float seekForce = 1);

	MathLibrary::Vector2 calculateForce(Agent* agent) override;
	void update(Agent* agent, float deltaTime) override;

private:
	float m_seekForce;
};