#include "ArrivalBehaviour.h"
#include "Agent.h"
#include "Actor.h"
#include <iostream>

ArrivalBehaviour::ArrivalBehaviour()
{
	m_target = nullptr;
	setForceScale(1);
}

ArrivalBehaviour::ArrivalBehaviour(Actor* target, float seekForce)
{
	m_target = target;
	setForceScale(seekForce);
}

MathLibrary::Vector2 ArrivalBehaviour::calculateForce(Agent* agent)
{

	float slowingRadius = 1.25f;
	MathLibrary::Vector2 desiredVelocity = MathLibrary::Vector2::normalize(m_target->getWorldPosition() - agent->getWorldPosition());
	float distance = desiredVelocity.getMagnitude();

	if (distance < slowingRadius)
		desiredVelocity = desiredVelocity * getForceScale() * (distance / slowingRadius);

	else
		desiredVelocity = desiredVelocity * getForceScale();

	//Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();

	return steeringForce;
}

void ArrivalBehaviour::update(Agent* agent, float deltaTime)
{
	//If the agent isn't null, calculate a new force and apply it to the agent.
	if (agent)
		agent->addForce(calculateForce(agent));
}
