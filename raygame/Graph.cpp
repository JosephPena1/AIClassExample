#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <raylib.h>
#include <deque>

Graph::Graph(int width, int height, int nodeSize, int nodeSpacing)
{
	m_width = width;
	m_height = height;

	createGraph(nodeSize, nodeSpacing);
}

void Graph::draw()
{
	for(int i = 0; i < m_nodes.size(); i++)
		m_nodes[i]->draw();
}

void Graph::update(float deltaTime)
{
	Actor::update(deltaTime);

	for (int i = 0; i < m_nodes.size(); i++)
		m_nodes[i]->update(deltaTime);
}

void Graph::BFS(int startX, int startY, int goalX, int goalY)
{
	//Gets a reference to the start and the end nodes
	Node* start = getNode(startX, startY);
	Node* goal = getNode(goalX, goalY);

	//If the start or the end is null, return
	if (!start || !goal)
		return;

	//Set the color to start and mark it as visited
	start->color = ColorToInt(GREEN);
	start->visited = true;

	//Set the iterator to be the start node
	Node* currentNode = start;
	//Creates a queue to store the nodes
	std::deque<Node*> queue;
	//Add the start node to the queue
	queue.push_front(start);

	//Search for the goal while the queue isn't empty
	while (!queue.empty())
	{
		//Set the current node to be the first item in the queue
		currentNode = queue[0];
		//Remove the first item from the queue
		queue.pop_front();

		//Check if the iterator is the goal node
		if (currentNode == goal)
		{
			//Set the current node color to be yellow to mark it as found
			currentNode->color = ColorToInt(YELLOW);
			return;
		}

		//If the node wasn't the goal loop through its edges to get its neighboUrs
		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			//Create a pointer to store the node at the other end of the edge
			Node* currentEdgeEnd = nullptr;

			//Set the pointer to be the opposite end of the edge
			if (currentNode == currentNode->edges[i]->connectedNode2)
				currentEdgeEnd = currentNode->edges[i]->connectedNode1;
			else
				currentEdgeEnd = currentNode->edges[i]->connectedNode2;

			//If the node at the opposite end hasn't been visited yet mark it as visited and add it to the queue
			if (!currentEdgeEnd->visited)
			{
				currentEdgeEnd->color = ColorToInt(RED);
				currentEdgeEnd->visited = true;
				queue.push_back(currentEdgeEnd);
			}
		}
	}

}

void Graph::dijkstra(int startX, int startY, int goalX, int goalY)
{
	Node* start = getNode(startX, startY);
	Node* goal = getNode(goalX, goalY);

	//Check if the start or the goal pointer is null
	//if so return an empty list
	if (!start || !goal)
		return;

	start->color = ColorToInt(GREEN);
	start->visited = true;

	//Create a node pointer that will act as an iterator
	Node* currentNode;

	std::deque<Node*> openList;
	std::deque<Node*> closedList;

	openList.push_back(start);

	//Loop while the open list is not empty
	while (!openList.empty())
	{
		//Sort the items in the open list by the g score
		for (int i = 0; i < openList.size() - 1; i++)
		{
			bool swapped = false;

			for (int j = 0; j < openList.size() - i - 1; j++)
			{
				if (openList[j]->gScore > openList[j + 1]->gScore)
				{
					Node* temp = openList[j];
					openList[j] = openList[j + 1];
					openList[j + 1] = temp;
					swapped = true;
				}

				if (!swapped)
					break;
			}
		}

		currentNode = openList[0];

		//If the current node is the goal
		//Change color and return new path found
		if (currentNode == goal)
		{
			currentNode->color = ColorToInt(YELLOW);
			return;
		}

		//Pop the first item off the open list
		openList.pop_front();
		//Add the first item to the closed list
		closedList.push_back(currentNode);

		//Loop through all of the edges for the iterator
		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			Node* currentEdgeEnd = nullptr;

			if (currentNode == currentNode->edges[i]->connectedNode2)
				currentEdgeEnd = currentNode->edges[i]->connectedNode1;

			else
				currentEdgeEnd = currentNode->edges[i]->connectedNode2;

			bool inList = false;

			//checks if currentEdge is in closedList
			for (int j = 0; j < closedList.size(); j++)
				if (currentEdgeEnd == closedList[j])
					inList = true;

			//Check if node at the end of the edge is in the closed list
			if (!inList)
			{
				//Create a float and set it to be the g score of the iterator plus the cost of the edge
				float gScoreTotal = currentNode->gScore + currentNode->edges[i]->cost;

				//checks if currentEdge is in openList
				for (int j = 0; j < openList.size(); j++)
					if (currentEdgeEnd == openList[j])
						inList = true;

				//Check if the node at the end of the edge is in the open list
				if (!inList)
				{
					currentEdgeEnd->color = ColorToInt(RED);
					//Set the nodes g score to be the g score calculated earlier
					currentEdgeEnd->gScore = gScoreTotal;
					//Set the nodes previous to be the iterator
					currentEdgeEnd->setPrevious(currentNode);
					//Add the node to the open list
					openList.push_front(currentEdgeEnd);

				}

				//Otherwise if the g score is less than the node at the end of the edge's g score...
				else if (currentNode->gScore < currentEdgeEnd->gScore)
				{
					currentEdgeEnd->color = ColorToInt(RED);
					//Set the nodes g score to be the g score calculated earlier
					currentEdgeEnd->gScore = gScoreTotal;
					//Set its previous to be the current node
					currentEdgeEnd->setPrevious(currentNode);
				}
			}
			//end if statement
		}
		//end loop
	}
	//end loop
}

void Graph::aStar(int startX, int startY, int goalX, int goalY)
{
	Node* start = getNode(startX, startY);
	Node* goal = getNode(goalX, goalY);

	//Check if the start or the goal pointer is null
	//if so return an empty list
	if (!start || !goal)
		return;

	start->color = ColorToInt(GREEN);
	start->visited = true;

	//Create a node pointer that will act as an iterator
	Node* currentNode;

	std::deque<Node*> openList;
	std::deque<Node*> closedList;

	openList.push_back(start);

	//Loop while the open list is not empty
	while (!openList.empty())
	{
		//Sort the items in the open list by the f score
		for (int i = 0; i < openList.size() - 1; i++)
		{
			bool swapped = false;

			for (int j = 0; j < openList.size() - i - 1; j++)
			{
				if (openList[j]->fScore > openList[j + 1]->fScore)
				{
					Node* temp = openList[j];
					openList[j] = openList[j + 1];
					openList[j + 1] = temp;
					swapped = true;
				}

				if (!swapped)
					break;
			}
		}

		currentNode = openList[0];

		//If the current node is the goal
		//Change color and return new path found
		if (currentNode == goal)
		{
			currentNode->color = ColorToInt(YELLOW);
			return;
		}

		//Pop the first item off the open list
		openList.pop_front();
		//Add the first item to the closed list
		closedList.push_back(currentNode);

		//Loop through all of the edges for the iterator
		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			Node* currentEdgeEnd = nullptr;

			if (currentNode == currentNode->edges[i]->connectedNode2)
				currentEdgeEnd = currentNode->edges[i]->connectedNode1;

			else
				currentEdgeEnd = currentNode->edges[i]->connectedNode2;

			bool inList = false;

			//checks if currentEdge is in closedList
			for (int j = 0; j < closedList.size(); j++)
				if (currentEdgeEnd == closedList[j])
					inList = true;

			//Check if node at the end of the edge is in the closed list
			if (!inList)
			{
				//Create a float and set it to be the g score of the iterator plus the cost of the edge
				float gScoreTotal = currentNode->gScore + currentNode->edges[i]->cost;
				//Create a float and set it to be the h score of the node at the end of the edge
				float hScoreTotal = heuristic(currentEdgeEnd, goal);
				//Create a float for the f score and set it to be the g score combined with the h score
				float fScoreTotal = gScoreTotal + hScoreTotal;

				//checks if currentEdge is in openList
				for (int j = 0; j < openList.size(); j++)
					if (currentEdgeEnd == openList[j])
						inList = true;

				//Check if the node at the end of the edge is in the open list
				if (!inList)
				{
					currentEdgeEnd->color = ColorToInt(RED);
					//Set the nodes g score to be the g score calculated earlier
					currentEdgeEnd->gScore = gScoreTotal;
					//Set the nodes h score to be the h score calculated earlier
					currentEdgeEnd->hScore = hScoreTotal;
					//Set the nodes f score to be the g score calculated earlier
					currentEdgeEnd->fScore = fScoreTotal;
					//Set the nodes previous to be the iterator
					currentEdgeEnd->setPrevious(currentNode);
					//Add the node to the open list
					openList.push_front(currentEdgeEnd);

				}

				//Otherwise if the g score is less than the node at the end of the edge's g score...
				else if (currentNode->gScore < currentEdgeEnd->gScore)
				{
					currentEdgeEnd->color = ColorToInt(RED);
					//Set the nodes g score to be the g score calculated earlier
					currentEdgeEnd->gScore = gScoreTotal;
					//Set the nodes h score to be the h score calculated earlier
					currentEdgeEnd->hScore = hScoreTotal;
					//Set the nodes f score to be the g score calculated earlier
					currentEdgeEnd->fScore = fScoreTotal;
					//Set its previous to be the current node
					currentEdgeEnd->setPrevious(currentNode);
				}
			}
			//end if statement
		}
		//end loop
	}
	//end loop
}

float Graph::heuristic(Node* current, Node* goal)
{
	MathLibrary::Vector2 distance = goal->graphPosition - current->graphPosition;
	float hScore = distance.getMagnitude();

	return hScore;
}

Node* Graph::getNode(int xPos, int yPos)
{
	if (xPos < 0 || xPos > m_width || yPos < 0 || yPos > m_height)
		return nullptr;

	for (int i = 0; i < m_nodes.size(); i++)
	{
		if (m_nodes[i]->graphPosition == MathLibrary::Vector2(xPos, yPos))
			return m_nodes[i];
	}

	return nullptr;
}

void Graph::createGraph(int nodeSize, int nodeSpacing)
{
	float xPos = 0;
	float yPos = 0;

	//Loops for the amount of nodes in the graph
	for (int i = 0; i < m_width * m_height; i++)
	{
		//Creates a new node with the current graph position and size
		Node* currentNode = new Node(xPos, yPos, nodeSize);

		//Set the local offset for the current node
		MathLibrary::Vector2 nodeLocalPosition = { xPos * nodeSpacing, yPos * nodeSpacing };
		currentNode->setLocalPosition(nodeLocalPosition);

		//Add the node as a child of the grid and update the list
		addChild(currentNode);
		m_nodes.push_back(currentNode);

		//Connect the node to all nodes in range
		for (int j = 0; j < m_nodes.size(); j++)
		{
			//Finds the displacement between the current node being added and the node being evaluated
			MathLibrary::Vector2 displacement = m_nodes[j]->graphPosition - currentNode->graphPosition;

			//Check if the magnitude of the displacement is farther than the maximum
			if (displacement.getMagnitude() <= 1.42f && displacement.getMagnitude() > 0)
			{
				//Create a new edge that connects the two nodes
				Edge* currentEdge = new Edge(m_nodes[j], currentNode);
				currentNode->edges.push_back(currentEdge);
				m_nodes[j]->edges.push_back(currentEdge);
			}
		}

		//Increase the graph position on the x
		xPos++;

		//If the x position is greater than the width, reset it to 0 and increase the y
		if (xPos >= m_width)
		{
			xPos = 0;
			yPos++;
		}
	}
}
