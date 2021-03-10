#include "Agent.h"
#include "Behaviour.h"
#include "Game.h"

Agent::Agent() : Actor()
{
	m_force = { 0, 0 };
	m_maxForce = 1;
}

Agent::~Agent()
{
}

Agent::Agent(float x, float y, float collisionRadius, char icon, float maxSpeed, float maxForce) :
	Actor(x, y, collisionRadius, icon, maxSpeed)
{
	m_force = { 0, 0 };
	m_maxForce = maxForce;
}

Agent::Agent(float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed, float maxForce) :
	Actor(x, y, collisionRadius, sprite, maxSpeed)
{
	m_force = { 0, 0 };
	m_maxForce = maxForce;
}

Agent::Agent(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float maxForce) :
	Actor(x, y, collisionRadius, spriteFilePath, maxSpeed)
{
	m_force = { 0, 0 };
	m_maxForce = maxForce;
}

void Agent::update(float deltaTime)
{
	//checks if Agent is inside the windows boundary
	int screenWidth = Game::getScreenWidth() / 32;
	int screenHeight = Game::getScreenHeight() / 32;

	if (getWorldPosition().x > screenWidth)
		setWorldPostion(MathLibrary::Vector2{ 0, getWorldPosition().y });
	if (getWorldPosition().x < -1)
		setWorldPostion(MathLibrary::Vector2{ (float)screenWidth, getWorldPosition().y });

	if (getWorldPosition().y > screenHeight)
		setWorldPostion(MathLibrary::Vector2{ getWorldPosition().x, 0 });
	if (getWorldPosition().y < -1)
		setWorldPostion(MathLibrary::Vector2{ getWorldPosition().x, (float)screenHeight });

	//Reset force to be zero
	m_force = { 0, 0 };

	//Calls update for each behaviour in the list
	for(int i = 0; i < m_behaviours.size(); i++)
	{
		m_behaviours[i]->update(this, deltaTime);
	}

	//Updates velocity with the new force
	setVelocity(getVelocity() + m_force * deltaTime);

	//Rotates the agent to face the direction it's moving in
	updateFacing();

	Actor::update(deltaTime);
}

void Agent::addForce(MathLibrary::Vector2 force)
{
	//Add the force given to the total force
	m_force = m_force + force;

	//If the total force is greater than the max force, set its magnitude to be the max force
	if (m_force.getMagnitude() > getMaxForce())
		m_force = m_force.getNormalized() * getMaxForce();
}

void Agent::addBehaviour(Behaviour* behaviour)
{
	if(behaviour)
		m_behaviours.push_back(behaviour);
}
