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

	m_pCurrentNode = *itNode;

	if(m_pCurrentNode == m_pGoal)
		return true;
	
	m_OpenNodes.erase(itNode);
	m_ClosedNodes.push_back(m_pCurrentNode);
	
	for(Node* pNeighbor : m_pCurrentNode->neighbors)
	{
		bool isNewPath = false;

		if(pNeighbor->isWall)
			continue;

		if(std::find(m_ClosedNodes.begin(), m_ClosedNodes.end(), pNeighbor) != m_ClosedNodes.end())
			continue;

		float tempG = m_pCurrentNode->g + 1;

		if(std::find(m_OpenNodes.begin(), m_OpenNodes.end(), pNeighbor) != m_OpenNodes.end())
		{
			if(tempG < pNeighbor->g)
			{
				pNeighbor->g = tempG;
				isNewPath = true;
			}
		}
		else
		{
			pNeighbor->g = tempG;
			m_OpenNodes.push_back(pNeighbor);
			isNewPath = true;
		}

		if(isNewPath)
		{
			pNeighbor->h = Heuristic(*pNeighbor, *m_pGoal);
			pNeighbor->f = pNeighbor->g + pNeighbor->h;
			pNeighbor->pPrevious = m_pCurrentNode;
		}
	}

	return false;
}

const float PathFinder::Heuristic(const Node& n1, const Node& n2) const
{
	return EuclidianDistance(n1, n2);
	// return ManhattanDistance(n1, n2);
}

const float PathFinder::ManhattanDistance(const Node & n1, const Node & n2) const
{
	return fabs(n1.coordinates.x - n2.coordinates.x) + fabs(n1.coordinates.y - n2.coordinates.y);
}

const float PathFinder::EuclidianDistance(const Node & n1, const Node & n2) const
{
	const float dx = n1.coordinates.x - n2.coordinates.x;
	const float dy = n1.coordinates.y - n2.coordinates.y;
	
	return sqrtf(dx * dx + dy * dy);
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
