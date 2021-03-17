#include "SeePlayer.h"
#include "ComplexEnemy.h"

void SeePlayer::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);

	if (checkCondition(agent, deltaTime))
		ABDecision::makeDecision(agent, deltaTime);

	else
		ABDecision::makeDecision(agent, deltaTime);

}

bool SeePlayer::checkCondition(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);

	if (enemy->checkTargetInSight(1))
		return true;

	return false;
}
