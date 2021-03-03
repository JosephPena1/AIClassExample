#include "PursueBehaviour.h"
#include "Agent.h"
#include "Actor.h"

PursueBehaviour::PursueBehaviour()
{
	m_target = nullptr;
	m_seekForce = 1;
}

PursueBehaviour::PursueBehaviour(Actor* target, float seekForce)
{
	m_target = target;
	m_seekForce = seekForce;
}

MathLibrary::Vector2 PursueBehaviour::calculateForce(Agent* agent)
{
	//Find the direction to move in.
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize((m_target->getWorldPosition() + m_target->getVelocity()) - agent->getWorldPosition());

	//Scale the direction vector by the seek force
	MathLibrary::Vector2 desiredVelocity = direction * m_seekForce;

	//Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();

	return steeringForce;
}

void PursueBehaviour::update(Agent* agent, float deltaTime)
{
	//If the agent isn't null, calculate a new force and apply it to the agent.
	if (agent)
		agent->addForce(calculateForce(agent));
}
