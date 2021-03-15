#include "WanderDecision.h"
#include "ComplexEnemy.h"
#include "WanderBehaviour.h"
#include "PursueBehaviour.h"
#include "EvadeBehaviour.h"

void WanderDecision::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);

	if (enemy)
	{
		enemy->getWander()->setEnabled(true);
		enemy->getPursue()->setEnabled(false);
		enemy->getEvade()->setEnabled(false);
	}
}
