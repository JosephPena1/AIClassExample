#include "EvadeBehaviour.h"
#include "Agent.h"
#include "Actor.h"

EvadeBehaviour::EvadeBehaviour()
{
	m_target = nullptr;
	setForceScale(1);
}

EvadeBehaviour::EvadeBehaviour(Actor* target, float fleeForce)
{
	m_target = target;
	setForceScale(fleeForce);
}

MathLibrary::Vector2 EvadeBehaviour::calculateForce(Agent* agent)
{
	//Find the direction to move in.
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(agent->getWorldPosition() - (m_target->getWorldPosition() + m_target->getVelocity()));

	//Scale the direction vector by the seek force
	MathLibrary::Vector2 desiredVelocity = direction * getForceScale();

	//Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();

	return steeringForce;
}

void EvadeBehaviour::update(Agent* agent, float deltaTime)
{
	//If the agent isn't null, calculate a new force and apply it to the agent.
	if (agent)
		agent->addForce(calculateForce(agent));
}
