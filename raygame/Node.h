#pragma once
#include "Actor.h"
#include <vector>

class Edge;

class Node : public Actor
{
public:
	Node(int x, int y, int nodeSize);
	std::vector<Edge*> edges;
	MathLibrary::Vector2 graphPosition;
	int color = 0xFFFFFFFF;
	int size = 1;
	bool visited;
	float gScore;
	float hScore;
	float fScore;
	void draw() override;
	void update(float deltaTime) override;
	void setPrevious(Node* previous) { m_previous = previous; }
	Node* getPrevious() { return m_previous; };

private:
	Node* m_previous;
};