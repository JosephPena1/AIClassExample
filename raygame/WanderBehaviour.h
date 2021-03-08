#pragma once
#include "SteeringBehaviour.h"

class Actor;

class WanderBehaviour : public SteeringBehaviour
{
public:
	WanderBehaviour();
	WanderBehaviour(float wanderForce = 1);

	MathLibrary::Vector2 calculateForce(Agent* agent) override;
	void update(Agent* agent, float deltaTime) override;
	void draw(Agent* agent) override;

private:
	float m_circleRadius;
	MathLibrary::Vector2 m_circlePos;
	MathLibrary::Vector2 m_targetPos;
};