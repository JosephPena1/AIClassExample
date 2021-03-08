#include "SimpleEnemy.h"
#include "SeekBehaviour.h"
#include "WanderBehaviour.h"

bool SimpleEnemy::checkTargetInSight()
{
	//Check if target is null, return false if true
	if (!getTarget())
		return false;

	MathLibrary::Vector2 direction = (getTarget()->getWorldPosition() - getWorldPosition()).getNormalized();

	//Find the dot product of the enemy's forward and the direction vector
	MathLibrary::Vector2 dotProd = MathLibrary::Vector2::dotProduct(getForward(), direction);

	//Find the angle using the dot product

	//check if the angle is greater than the Enemy's viewing angle

	return false;
}

void SimpleEnemy::onCollision(Actor* other)
{
	//Checks to see if the enemy ran into the player

	//If the enemy ran into the player, deal damage to the player

	//If the player's health is less than 0, set target to nullptr
}

void SimpleEnemy::start()
{
	//Call base start function
	Enemy::start();

	//Set the default state of the enemy
	m_currentState = WANDER;

	//Initialize member variables
	m_seek = getBehaviour<SeekBehaviour>();
	m_wander = getBehaviour<WanderBehaviour>();

	//Set the target to be the base class target
	setTarget(Enemy::getTarget());
}

void SimpleEnemy::update(float deltaTime)
{
	//Create a switch statement for the state machine

	//The switch should transition to wander state if the target is not in sight.
	//You can set wander force to be whatever value you see fit, but be sure to
	//set the seek force to be 0.

	//The switch should transition to seek state if the target is in sight.
	//You can set seek force to be whatever value you see fit, but be sure to
	//set the wander force to 0.

	Enemy::update(deltaTime);
}

void SimpleEnemy::setTarget(Actor* target)
{
	Enemy::setTarget(target);
	m_seek->setTarget(target);
}
