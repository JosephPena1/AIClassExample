#pragma once
#include "Enemy.h"

enum EnemyState
{
	WANDER,
	PURSUE,
	FLEE
};

class WanderBehaviour;
class PursueBehaviour;
class ArrivalBehaviour;
class FleeBehaviour;

class SimpleEnemy : public Enemy
{
public:
	using Enemy::Enemy;
	bool checkTargetInSight();

	void tag(Actor* other);
	void onCollision(Actor* other) override;
	void start() override;
	void update(float deltaTime) override;

	void setTarget(Actor* target) override;

private:
	EnemyState m_currentState;
	WanderBehaviour* m_wander;
	PursueBehaviour* m_pursue;
	ArrivalBehaviour* m_arrival;
	FleeBehaviour* m_flee;

	int m_cooldown;

};