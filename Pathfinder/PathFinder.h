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

	Node* GetNode(int x, int y);

	size_t m_Width;
	size_t m_Height;
	std::vector<Node> m_Grid;

private:
	std::vector<Node*> m_OpenNodes;
	std::vector<Node*> m_VisitedNodes;

	Node* m_pStart = nullptr;
	Node* m_pGoal = nullptr;
};
