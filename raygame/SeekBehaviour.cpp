#include "SeekBehaviour.h"
#include "Agent.h"

MathLibrary::Vector2 SeekBehaviour::calculateForce(Agent* owner)
{
	//Do seek behaviour
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(owner->getWorldPosition() - m_target->getWorldPosition());


	return MathLibrary::Vector2();
}
