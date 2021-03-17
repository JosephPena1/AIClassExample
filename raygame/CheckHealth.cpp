#include "CheckHealth.h"
#include "ComplexEnemy.h"

void CheckHealth::makeDecision(Agent* agent, float deltaTime)
{
	if (checkCondition(agent, deltaTime))
		ABDecision::makeDecision(agent, deltaTime);

	else
		ABDecision::makeDecision(agent, deltaTime);

}

bool CheckHealth::checkCondition(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);
	if (enemy->getHealth() < 2)
		return true;

	return false;
}
