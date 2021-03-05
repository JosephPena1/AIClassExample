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

	//generates two random numbers from -5 to 5
	float randNum = rand() % 11 + (-5);
	float randNum2 = rand() % 11 + (-5);

	//sets the center of the circle to be agents current velocity normalised
	MathLibrary::Vector2 circleCenter = agent->getWorldPosition() + agent->getForward() * agent->getForward().getMagnitude();

	//creates two random variables to make the offset
	float x = radian * cos(randNum);
	float y = radian * sin(randNum2);
	MathLibrary::Vector2 offset = {x, y};

	//creates a random target in the circle
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
