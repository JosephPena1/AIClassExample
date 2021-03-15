#include "ComplexEnemy.h"
#include "Player.h"
#include "WanderBehaviour.h"
#include "PursueBehaviour.h"
#include "EvadeBehaviour.h"

void ComplexEnemy::start()
{
	Enemy::start();

	//Initialize behaviours
	m_wanderBehaviour = getBehaviour<WanderBehaviour>();
	m_pursueBehaviour = getBehaviour<PursueBehaviour>();
	m_evadeBehaviour = getBehaviour<EvadeBehaviour>();

	//Set target to the target given from the base class
	setTarget(Enemy::getTarget());

}

void ComplexEnemy::update(float deltaTime)
{
	Enemy::update(deltaTime);
}

void ComplexEnemy::setTarget(Actor* target)
{
	Enemy::setTarget(target);
	m_pursueBehaviour->setTarget(target);
	m_evadeBehaviour->setTarget(target);
}

void ComplexEnemy::onCollision(Actor* other)
{
	Enemy::onCollision(other);

	Player* player = dynamic_cast<Player*>(other);

	//If the actor is a player, damage it.
	if (player)
	{
		player->takeDamage(getDamage());

		//If the player has died, set the target to be nullptr
		if (player->getHealth() <= 0)
			setTarget(nullptr);
	}
}

bool ComplexEnemy::checkTargetInSight(float angle)
{
	//Check if target is null, return false if true
	if (!getTarget())
		return false;

	//The direction the target is in
	MathLibrary::Vector2 direction = getTarget()->getWorldPosition() - getWorldPosition();

	//Finds the dot product of the enemy's forward and the direction vector
	float enemyAngle = MathLibrary::Vector2::dotProduct(getForward(), direction.getNormalized());

	//Finds the angle using the dot product
	angle = acos(MathLibrary::Vector2::findAngle(getForward(), direction.getNormalized()) / 1.5f);

	//Returns true if the angle is greater than the Enemy's viewing angle
	//and if the distance is less than the max distance
	if (angle > enemyAngle && checkTargetInRange(8))
		return true;

	return false;
}

bool ComplexEnemy::checkTargetInRange(float range)
{
	//The direction the target is in
	MathLibrary::Vector2 direction = getTarget()->getWorldPosition() - getWorldPosition();

	//gets the length of direction's vector
	float distance = direction.getMagnitude();

	//Returns true if the distance is less than the max distance
	if (distance <= range)
		return true;

	return false;
}
