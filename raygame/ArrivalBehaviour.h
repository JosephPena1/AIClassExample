#pragma once
#include "SteeringBehaviour.h"

class Actor;

class ArrivalBehaviour : public SteeringBehaviour
{
public:
	ArrivalBehaviour();
	ArrivalBehaviour(Actor* target, float seekForce = 1);

	Actor* getTarget() { return m_target; }
	void setTarget(Actor* target) { m_target = target; }

	MathLibrary::Vector2 calculateForce(Agent* agent) override;
	void update(Agent* agent, float deltaTime) override;

private:
	//The actor the behaviour is seeking
	Actor* m_target;
	float m_seekForce;
};