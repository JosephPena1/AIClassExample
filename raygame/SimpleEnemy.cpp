#include "SimpleEnemy.h"
#include <iostream>
#include "Player.h"
#include "PursueBehaviour.h"
#include "ArrivalBehaviour.h"
#include "EvadeBehaviour.h"

bool SimpleEnemy::checkTargetInSight()
{
	//Max distance the enemy can see
	float maxDistance = 8;

	//Check if target is null, return false if true
	if (!getTarget())
		return false;

	//The direction the target is in
	MathLibrary::Vector2 direction = getTarget()->getWorldPosition() - getWorldPosition();

	//gets the length of direction's vector
	float distance = direction.getMagnitude();

	//Finds the dot product of the enemy's forward and the direction vector
	float enemyAngle = MathLibrary::Vector2::dotProduct(getForward(), direction.getNormalized());

	//Finds the angle using the dot product
	float angle = acos(MathLibrary::Vector2::findAngle(getForward(), direction.getNormalized()) / 2);

	//Checks if the angle is greater than the Enemy's viewing angle 
	//and if the distance is less than the max distance
	if (angle > enemyAngle && distance <= maxDistance)
		return true;

	return false;
}

void SimpleEnemy::tag(Actor* other)
{
	//if other is a nullptr return
	if (!other)
		return;

	//Checks if the Actor passed in is a Player type
	Player* player = dynamic_cast<Player*>(other);

	//Checks to see if the enemy ran into the player
	if (checkCollision(player))
	{
		if (m_cooldown <= 0)
		{
			switch (m_currentState)
			{
			case EVADE:
				m_currentState = PURSUE;
				break;
			case PURSUE:
				m_currentState = EVADE;
				break;
			}
		}
	}
}

void SimpleEnemy::onCollision(Actor* other)
{
	//if other is a nullptr return
	if (!other)
		return;

	//Checks if the Actor passed in is a Player type
	Player* player = dynamic_cast<Player*>(other);

	//Checks to see if the enemy ran into the player
	if (checkCollision(player))
	{
		//If the enemy ran into the player, deal damage to the player
		player->takeDamage(getDamage());
	}

	//If the player's health is less than 0, set target to nullptr
	if (player->getHealth() <= 0)
	{
		setTarget(nullptr);
		m_pursue->setTarget(nullptr);
		m_arrival->setTarget(nullptr);
		m_evade->setTarget(nullptr);
	}
}

void SimpleEnemy::start()
{
	//Call base start function
	Enemy::start();

	//Set the default state of the enemy
	m_currentState = PURSUE;

	//Initialize member variables
	m_pursue = getBehaviour<PursueBehaviour>();
	m_arrival = getBehaviour<ArrivalBehaviour>();
	m_evade = getBehaviour<EvadeBehaviour>();

	//Set the target to be the base class target
	setTarget(Enemy::getTarget());
}

void SimpleEnemy::update(float deltaTime)
{
	std::cout << m_currentState << std::endl;

	//Create a switch statement for the state machine
	tag(getTarget());

	if (m_cooldown <= 0)
	{
		switch (m_currentState)
		{
		case PURSUE:
			m_pursue->setForceScale(50);
			m_arrival->setForceScale(30);
			m_evade->setForceScale(0);
			m_cooldown = 120;
			break;

		case EVADE:
			m_evade->setForceScale(5);
			m_pursue->setForceScale(0);
			m_arrival->setForceScale(0);
			m_cooldown = 120;
			break;

		default:
			break;
		}
	}
	
	m_cooldown--;
	
	Enemy::update(deltaTime);
}

void SimpleEnemy::setTarget(Actor* target)
{
	Enemy::setTarget(target);
	m_pursue->setTarget(target);
	m_arrival->setTarget(target);
	m_evade->setTarget(target);
}
