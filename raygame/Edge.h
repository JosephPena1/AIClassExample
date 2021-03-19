#pragma once
#include "Actor.h"
#include <random>

class Node;

class Edge : public Actor
{
public:
	Edge(Node* node1, Node* node2);
	Node* connectedNode1;
	Node* connectedNode2;
	float cost = rand() % 4;
	void draw() override;
	void update(float deltaTime) override;

};