#include "Enemy.h"

Enemy::Enemy(float x, float y, float collisionRadius, const char* spriteFilePath, Agent* target, float maxSpeed = 1, float maxForce = 1)
{
	m_target = target;
}

void Enemy::update(float deltaTime)
{

}
