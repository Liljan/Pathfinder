#include "SFML/Graphics.hpp"

#include "PathFinder.h"

void DrawPathFinder(sf::RenderWindow& window, PathFinder& pathFinder)
{
	const sf::Vector2u size = window.getSize();

	const float width = static_cast<float>(window.getSize().x / pathFinder.m_Width);
	const float height = static_cast<float>(window.getSize().y / pathFinder.m_Height);

	for(const auto& node : pathFinder.m_Grid)
	{
		const float x = node.coordinates.x * width;
		const float y = node.coordinates.y * height;

		sf::RectangleShape rect(sf::Vector2f(width - 1.0f, height - 1.0f));
		rect.setPosition(sf::Vector2f(x, y));

		if(node.isWall)
		{
			rect.setFillColor(sf::Color(0, 0, 0, 255));
			rect.setOutlineColor(sf::Color(50, 50, 50, 255));
		}
		else
		{
			rect.setFillColor(sf::Color(25, 25, 25, 255));
			rect.setOutlineColor(sf::Color(50, 50, 50, 255));
		}

		rect.setOutlineThickness(2.0f);

		window.draw(rect);
	}

	for(const auto& pNode : pathFinder.GetClosedNodes())
	{
		const float x = pNode->coordinates.x * width;
		const float y = pNode->coordinates.y * height;

		sf::RectangleShape rect(sf::Vector2f(width - 1.0f, height - 1.0f));
		rect.setPosition(sf::Vector2f(x, y));

		rect.setFillColor(sf::Color(255, 0, 0, 255));
		rect.setOutlineColor(sf::Color(50, 50, 50, 255));

		rect.setOutlineThickness(2.0f);

		window.draw(rect);
	}

	for(const auto& pNode : pathFinder.GetOpenNodes())
	{
		const float x = pNode->coordinates.x * width;
		const float y = pNode->coordinates.y * height;

		sf::RectangleShape rect(sf::Vector2f(width - 1.0f, height - 1.0f));
		rect.setPosition(sf::Vector2f(x, y));

		rect.setFillColor(sf::Color(0, 255, 0, 255));
		rect.setOutlineColor(sf::Color(50, 50, 50, 255));

		rect.setOutlineThickness(2.0f);

		window.draw(rect);
	}

	if(const Node* pCurrent = pathFinder.GetCurrentNode())
	{
		while(pCurrent)
		{
			const float x = pCurrent->coordinates.x * width;
			const float y = pCurrent->coordinates.y * height;

			sf::RectangleShape rect(sf::Vector2f(width - 1.0f, height - 1.0f));
			rect.setPosition(sf::Vector2f(x, y));

			rect.setFillColor(sf::Color(0, 0, 255, 255));
			rect.setOutlineColor(sf::Color(50, 50, 50, 255));

			rect.setOutlineThickness(2.0f);

			window.draw(rect);

			pCurrent = pCurrent->pPrevious;
		}
		
	}

}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "My window");
	window.setFramerateLimit(60);

	PathFinder pathFinder(sf::Vector2u(25, 25));
	pathFinder.Setup(sf::Vector2i(0, 0), sf::Vector2i(24, 24), 0.1f);

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