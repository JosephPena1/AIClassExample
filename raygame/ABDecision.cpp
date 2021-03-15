#include "ABDecision.h"

ABDecision::ABDecision(Decision* leftChild, Decision* rightChild)
{
	m_leftChild = leftChild;
	m_rightChild = rightChild;
}

void ABDecision::makeDecision(Agent* agent, float deltaTime)
{
	//Calls the checkCondition function for the decision
	if (checkCondition(agent, deltaTime))
	{
		//If the function returns true and if the left child isn't null,
		//move to the left node
		if (m_leftChild)
			m_leftChild->makeDecision(agent, deltaTime);
	}
	else
	{
		//If the function returns false and if the right child isn't null,
		//move to the right node
		if (m_rightChild)
			m_rightChild->makeDecision(agent, deltaTime);
	}
}

bool ABDecision::checkCondition(Agent* agent, float deltaTime)
{

	return false;
}