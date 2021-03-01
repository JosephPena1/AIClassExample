#pragma once

class Agent;

//Abstract class for all behaviours.
class Behaviour
{
public:
	virtual void update(Agent* owner, float deltaTime) = 0;
};