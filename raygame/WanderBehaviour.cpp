#include "WanderBehaviour.h"
#include "Agent.h"
#include "Actor.h"
#include <random>

WanderBehaviour::WanderBehaviour()
{
	m_seekForce = 1;
}

WanderBehaviour::WanderBehaviour(float seekForce)
{
	m_seekForce = 1;
}

MathLibrary::Vector2 WanderBehaviour::calculateForce(Agent* agent)
{
	float radian = 1;
	float randNum = rand() % 10 + 1;
	//sets the center of the circle to be agents current velocity normalised
	MathLibrary::Vector2 direction = agent->getVelocity().getNormalized();
	MathLibrary::Vector2 circleCenter = agent->getWorldPosition() + direction * 1;
	float x = radian * cos(randNum);
	float y = radian * sin(randNum);
	MathLibrary::Vector2 offset = {x, y};

	MathLibrary::Vector2 target = circleCenter + offset;

	//Find the direction to move in.
	MathLibrary::Vector2 direction2 = MathLibrary::Vector2::normalize(target - agent->getWorldPosition());

	//Scale the direction vector by the seek force
	MathLibrary::Vector2 desiredVelocity = direction2 * m_seekForce;

	//Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();

	return steeringForce;
}

void WanderBehaviour::update(Agent* agent, float deltaTime)
{
	if (agent)
		agent->addForce(calculateForce(agent));
}
