#pragma once
#include "Enemy.h"


class WanderBehaviour;
class PursueBehaviour;
class EvadeBehaviour;

class ComplexEnemy : public Enemy
{
public:
	using Enemy::Enemy;
	void start() override;
	void update(float deltaTime) override;

	void setTarget(Actor* target) override;
	void onCollision(Actor* other) override;
	bool checkTargetInSight(float angle = 2);
	bool checkTargetInRange(float range);

	WanderBehaviour* getWander() { return m_wanderBehaviour; }
	PursueBehaviour* getPursue() { return m_pursueBehaviour; }
	EvadeBehaviour* getEvade() { return m_evadeBehaviour; }

private:
	WanderBehaviour* m_wanderBehaviour;
	PursueBehaviour* m_pursueBehaviour;
	EvadeBehaviour* m_evadeBehaviour;

};