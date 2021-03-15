#include "PursueDecision.h"
#include "ComplexEnemy.h"
#include "WanderBehaviour.h"
#include "PursueBehaviour.h"
#include "EvadeBehaviour.h"

void PursueDecision::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);

	if (enemy)
	{
		enemy->getPursue()->setEnabled(true);
		enemy->getWander()->setEnabled(false);
		enemy->getEvade()->setEnabled(false);
	}
}
