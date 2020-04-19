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

	std::vector<Node> grid;

private:
	std::vector<Node*> openNodes;
	std::vector<Node*> visitedNodes;
};

