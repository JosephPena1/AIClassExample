#include "CheckHealth.h"
#include "ComplexEnemy.h"

void CheckHealth::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);

	if (enemy->getHealth())
		ABDecision::makeDecision(agent, deltaTime);

	else
		ABDecision::makeDecision(agent, deltaTime);

}
