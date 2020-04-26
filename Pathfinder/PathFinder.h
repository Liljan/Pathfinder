#pragma once

#include "SFML/System/Vector2.hpp"

#include <vector>

class Node
{
public:
	Node(const sf::Vector2i coordinates, bool isWall = false) : coordinates(coordinates)
	{
		this->isWall = isWall;
	}

	~Node() = default;

public:

	Node* pPrevious = nullptr;
	std::vector<Node*> neighbors;

	sf::Vector2i coordinates;

	float f = 0.0f;
	float g = 0.0f;
	float h = 0.0f;

	bool isWall = false;
};

class PathFinder
{
public:
	PathFinder(const sf::Vector2u size);
	~PathFinder();

	void Setup(const sf::Vector2i start, const sf::Vector2i end, const float wallChance);

	bool Solve();

	const float Heuristic(const Node& n1, const Node& n2) const;
	const float ManhattanDistance(const Node& n1, const Node& n2) const;
	const float EuclidianDistance(const Node& n1, const Node& n2) const;

	// For rendering, maybe kinda bad
	const std::vector<Node*> GetOpenNodes() { return m_OpenNodes; }
	const std::vector<Node*> GetClosedNodes() { return m_ClosedNodes; }
	const Node* GetStartNode() { return m_pStart; }
	const Node* GetGoalNode() { return m_pGoal; }

	size_t m_Width;
	size_t m_Height;
	std::vector<Node> m_Grid;

private:
	Node* GetNode(int x, int y);

	std::vector<Node*> m_OpenNodes;
	std::vector<Node*> m_ClosedNodes;

	Node* m_pStart = nullptr;
	Node* m_pGoal = nullptr;
};
