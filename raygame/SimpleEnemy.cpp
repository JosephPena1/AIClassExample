#include "SimpleEnemy.h"
#include "Player.h"
#include "SeekBehaviour.h"
#include "WanderBehaviour.h"

bool SimpleEnemy::checkTargetInSight()
{
	//Max distance the enemy can see
	float maxDistance = 12;

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
	float angle = acos(MathLibrary::Vector2::findAngle(getForward(), direction.getNormalized()));

	//Checks if the angle is greater than the Enemy's viewing angle 
	//and if the distance is less than the max distance
	if (angle > enemyAngle && distance <= maxDistance)
		return true;

	return false;
}

void SimpleEnemy::onCollision(Actor* other)
{
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
		m_seek->setTarget(nullptr);
	}
}

void SimpleEnemy::start()
{
	//Call base start function
	Enemy::start();

	//Set the default state of the enemy
	m_currentState = WANDER;

	//Initialize member variables
	m_wander = getBehaviour<WanderBehaviour>();
	m_seek = getBehaviour<SeekBehaviour>();

	//Set the target to be the base class target
	setTarget(Enemy::getTarget());
}

void SimpleEnemy::update(float deltaTime)
{
	//Create a switch statement for the state machine

	//The switch should transition to wander state if the target is not in sight.
	//You can set wander force to be whatever value you see fit, but be sure to
	//set the seek force to be 0.

	if (checkTargetInSight())
		m_currentState = SEEK;

	else
		m_currentState = WANDER;

	//The switch should transition to seek state if the target is in sight.
	//You can set seek force to be whatever value you see fit, but be sure to
	//set the wander force to 0.

	switch (m_currentState)
	{
	case WANDER:
		m_wander->setForceScale(3);
		m_seek->setForceScale(0);
		break;

	case SEEK:
		m_seek->setForceScale(3);
		m_wander->setForceScale(0);
		break;

	default:
		break;
	}
	
	Enemy::update(deltaTime);
}

void SimpleEnemy::setTarget(Actor* target)
{
	Enemy::setTarget(target);
	m_seek->setTarget(target);
}
