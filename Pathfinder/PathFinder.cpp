#include "PathFinder.h"

#include <algorithm>

PathFinder::PathFinder(const sf::Vector2u size)
{
	m_Width = size.x;
	m_Height = size.y;
	m_Grid.reserve(size.x * size.y);
}

PathFinder::~PathFinder()
{
}

void PathFinder::Setup(const sf::Vector2i start, const sf::Vector2i end, const float wallChance)
{
	for(size_t index = 0; index < m_Grid.capacity(); ++index)
	{
		const size_t x = index % m_Width;
		const size_t y = index / m_Width;

		const float spawnWallValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

		m_Grid.push_back(Node(sf::Vector2i(x, y), spawnWallValue < wallChance));
	}

	for(auto& node : m_Grid)
	{
		// Orthogonal first
		if(Node* pLeft = GetNode(node.coordinates.x - 1, node.coordinates.y))
			node.neighbors.push_back(pLeft);
		if(Node* pRight = GetNode(node.coordinates.x + 1, node.coordinates.y))
			node.neighbors.push_back(pRight);
		if(Node* pUp = GetNode(node.coordinates.x, node.coordinates.y - 1))
			node.neighbors.push_back(pUp);
		if(Node* pDown = GetNode(node.coordinates.x, node.coordinates.y + 1))
			node.neighbors.push_back(pDown);
	}

	m_pStart = GetNode(start.x, start.y);
	m_pStart->isWall = false;
	
	m_pGoal = GetNode(end.x, end.y);
	m_pGoal->isWall = false;

	m_OpenNodes.push_back(m_pStart);
}

bool PathFinder::Solve()
{
	// No solution or end
	if(m_OpenNodes.size() == 0)
		return true;

	auto itNode = std::min_element(m_OpenNodes.begin(), m_OpenNodes.end(), [](Node* pNode0, Node* pNode1) {
		return pNode0->f < pNode1->f;
	});

	Node* pCurrentNode = *itNode;

	if(pCurrentNode == m_pGoal)
		return true;

	m_VisitedNodes.push_back(pCurrentNode);
	m_OpenNodes.erase(itNode);

	for(Node* pNeighbor : pCurrentNode->neighbors)
	{

	}

	/*	for(var i = 0; i < current.neighbors.length; ++i)
		{
			var neighbor = current.neighbors[i];

			var newPath = false;

			if(neighbor.wall)
				continue;

			if(closedList.includes(neighbor))
				continue;

			var tempG = current.g + 1;

			if(openList.includes(neighbor))
			{
				if(tempG < neighbor.g)
				{
					neighbor.g = tempG;
					newPath = true;
				}
			}
			else
			{
				neighbor.g = tempG;
				openList.push(neighbor);
				newPath = true;
			}

			if(newPath)
			{
				neighbor.h = heuristic(neighbor, end);
				neighbor.f = neighbor.g + neighbor.h;
				neighbor.previous = current;
			}
		}*/

	return false;
}

Node* PathFinder::GetNode(int x, int y)
{
	if(x < 0 || x > m_Width - 1)
		return nullptr;
	if(y < 0 || y > m_Height - 1)
		return nullptr;

	const int linearIndex = x + y * m_Width;

	return &m_Grid[linearIndex];
}
