#include "SimpleEnemy.h"
#include <iostream>
#include "Player.h"
#include "PursueBehaviour.h"
#include "WanderBehaviour.h"
#include "ArrivalBehaviour.h"
#include "FleeBehaviour.h"

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
		switch (m_currentState)
		{
		case FLEE:
			m_currentState = PURSUE;
			break;
		case PURSUE:
			m_currentState = FLEE;
			break;
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
		m_flee->setTarget(nullptr);
	}
}

void SimpleEnemy::start()
{
	//Call base start function
	Enemy::start();

	//Set the default state of the enemy
	m_currentState = PURSUE;

	//Initialize member variables
	m_wander = getBehaviour<WanderBehaviour>();
	m_pursue = getBehaviour<PursueBehaviour>();
	m_arrival = getBehaviour<ArrivalBehaviour>();
	m_flee = getBehaviour<FleeBehaviour>();

	//Set the target to be the base class target
	setTarget(Enemy::getTarget());
}

void SimpleEnemy::update(float deltaTime)
{
	std::cout << m_currentState << std::endl;

	//Create a switch statement for the state machine
	tag(getTarget());

	//The switch should transition to wander state if the target is not in sight.
	//You can set wander force to be whatever value you see fit, but be sure to
	//set the seek force to be 0.

	if (checkTargetInSight())
		m_currentState;

	/*else
		m_currentState = WANDER;*/

	//The switch should transition to seek state if the target is in sight.
	//You can set seek force to be whatever value you see fit, but be sure to
	//set the wander force to 0.

	switch (m_currentState)
	{
	case WANDER:
		m_wander->setForceScale(3);
		m_pursue->setForceScale(0);
		m_arrival->setForceScale(0);
		m_flee->setForceScale(0);
		break;

	case PURSUE:
		m_pursue->setForceScale(5);
		m_arrival->setForceScale(3);
		m_wander->setForceScale(0);
		m_flee->setForceScale(0);
		break;

	case FLEE:
		m_flee->setForceScale(3);
		m_pursue->setForceScale(0);
		m_arrival->setForceScale(0);
		m_wander->setForceScale(0);

	default:
		break;
	}
	
	Enemy::update(deltaTime);
}

void SimpleEnemy::setTarget(Actor* target)
{
	Enemy::setTarget(target);
	m_pursue->setTarget(target);
	m_arrival->setTarget(target);
	m_flee->setTarget(target);
}
