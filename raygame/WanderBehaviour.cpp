#include "WanderBehaviour.h"
#include "Agent.h"
#include "Actor.h"
#include "raylib.h"
#include <random>

WanderBehaviour::WanderBehaviour()
{
	setForceScale(1);
	m_circleRadius = 0;
	m_circlePos = {0, 0};
	m_targetPos = {0, 0};
}

WanderBehaviour::WanderBehaviour(float wanderForce)
{
	setForceScale(wanderForce);
	m_circleRadius = 0;
	m_circlePos = { 0, 0 };
	m_targetPos = { 0, 0 };
}

MathLibrary::Vector2 WanderBehaviour::calculateForce(Agent* agent)
{
	float radian = 1;
	m_circleRadius = radian;

	//generates two random numbers from -5 to 5
	float randNum = rand() % 11 + (-5);
	float randNum2 = rand() % 11 + (-5);

	//sets the center of the circle to be agents current velocity normalized
	MathLibrary::Vector2 circleCenter = agent->getWorldPosition() + agent->getForward() * agent->getForward().getMagnitude();
	m_circlePos = circleCenter;

	//creates two random variables to make the offset
	float x = radian * cos(randNum);
	float y = radian * sin(randNum2);
	MathLibrary::Vector2 offset = {x, y};

	//creates a random target in the circle
	MathLibrary::Vector2 target = circleCenter + offset;
	m_targetPos = target;

	//Find the direction to move in.
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(target - agent->getWorldPosition());

	//Scale the direction vector by the seek force
	MathLibrary::Vector2 desiredVelocity = direction * getForceScale();

	//Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();

	return steeringForce;
}

void WanderBehaviour::draw(Agent* agent)
{
	DrawCircle(m_circlePos.x * 32, m_circlePos.y * 32, m_circleRadius * 32, BLUE);
	DrawLine(m_circlePos.x * 32, m_circlePos.y * 32, m_targetPos.x * 32, m_targetPos.y * 32, RED);
}

void WanderBehaviour::update(Agent* agent, float deltaTime)
{
	if (agent)
		agent->addForce(calculateForce(agent));
}
