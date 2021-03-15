#include "EvadeDecision.h"
#include "ComplexEnemy.h"
#include "WanderBehaviour.h"
#include "PursueBehaviour.h"
#include "EvadeBehaviour.h"

void EvadeDecision::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);

	if (enemy)
	{
		enemy->getEvade()->setEnabled(true);
		enemy->getPursue()->setEnabled(false);
		enemy->getWander()->setEnabled(false);
	}
}
