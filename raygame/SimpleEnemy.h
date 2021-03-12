#pragma once
#include "Enemy.h"

enum EnemyState
{
	PURSUE,
	EVADE
};

class PursueBehaviour;
class ArrivalBehaviour;
class EvadeBehaviour;

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
	PursueBehaviour* m_pursue;
	ArrivalBehaviour* m_arrival;
	EvadeBehaviour* m_evade;

	int m_cooldown;

};