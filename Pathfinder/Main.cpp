#include "SFML/Graphics.hpp"

#include "PathFinder.h"

void DrawNode(sf::RenderWindow& window, const Node& node, const sf::Vector2f& size, const sf::Color& color)
{
	const float x = node.coordinates.x * size.x;
	const float y = node.coordinates.y * size.y;

	sf::RectangleShape rect(sf::Vector2f(size.x - 1.0f, size.y - 1.0f));
	rect.setPosition(sf::Vector2f(x, y));

	rect.setFillColor(color);
	rect.setOutlineColor(sf::Color(50, 50, 50, 255));

	rect.setOutlineThickness(2.0f);

	window.draw(rect);
}

void DrawPathFinder(sf::RenderWindow& window, PathFinder& pathFinder)
{
	const sf::Vector2u size = window.getSize();

	const float width = static_cast<float>(window.getSize().x / pathFinder.m_Width);
	const float height = static_cast<float>(window.getSize().y / pathFinder.m_Height);

	const sf::Vector2f dimensions(width, height);

	for(const auto& node : pathFinder.m_Grid)
	{
		sf::Color color = node.isWall ? sf::Color(0, 0, 0, 255) : sf::Color(25, 25, 25, 255);
		DrawNode(window, node, dimensions, color);
	}

	for(const auto& pNode : pathFinder.GetClosedNodes())
		DrawNode(window, *pNode, dimensions, sf::Color::Red);

	for(const auto& pNode : pathFinder.GetOpenNodes())
		DrawNode(window, *pNode, dimensions, sf::Color::Green);

	if(const Node* pCurrentNode = pathFinder.GetCurrentNode())
	{
		while(pCurrentNode)
		{
			DrawNode(window, *pCurrentNode, dimensions, sf::Color::Blue);
			pCurrentNode = pCurrentNode->pPrevious;
		}
	}

	DrawNode(window, *pathFinder.GetStartNode(), dimensions, sf::Color::Cyan);
	DrawNode(window, *pathFinder.GetGoalNode(), dimensions, sf::Color::Cyan);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "My window");
	//window.setFramerateLimit(60);

	PathFinder pathFinder(sf::Vector2u(25, 25));
	pathFinder.Setup(sf::Vector2i(0, 0), sf::Vector2i(pathFinder.m_Width - 1, pathFinder.m_Height - 1), 0.3f);

	bool isSolved = false;

	// run the program as long as the window is open
	while(window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while(window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if(event.type == sf::Event::Closed)
				window.close();
		}

		if(!isSolved)
			isSolved = pathFinder.Solve();

		// Rendering
				// clear the window with black color
		window.clear(sf::Color::Black);

		DrawPathFinder(window, pathFinder);

		// end the current frame
		window.display();
	}

	return 0;
}