#pragma once
#include "SterringBehaviour.h"

class SeekBehaviour : public SteeringBehaviour
{
public:
	SeekBehaviour() { m_target = nullptr; }
	SeekBehaviour(Agent* target) { m_target = target; }

	Agent* getTarget() { return m_target; }
	void setTarget(Agent* target) { m_target = target; }

	MathLibrary::Vector2 calculateForce(Agent* owner) override;
	void update(Agent* owner, float deltaTime) override;

private:
	//The agent the behaviour is seeking
	Agent* m_target;
};