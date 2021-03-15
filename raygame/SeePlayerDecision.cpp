#include "SeePlayer.h"
#include "ComplexEnemy.h"

void SeePlayer::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);

	if (enemy->checkTargetInSight(1))
		ABDecision::makeDecision(agent, deltaTime);

	else
		ABDecision::makeDecision(agent, deltaTime);

}
