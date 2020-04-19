#include "SFML/Graphics.hpp"

#include "PathFinder.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "My window");
	window.setFramerateLimit(60);

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


		// Rendering
				// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		// window.draw(...);

		sf::RectangleShape myRect(sf::Vector2f(130, 100));
		myRect.setPosition(sf::Vector2f(300, 400));

		myRect.setFillColor(sf::Color(25,25,25,255));
		myRect.setOutlineColor(sf::Color(240, 0, 0, 255));
		myRect.setOutlineThickness(2.0f);

		window.draw(myRect);

		// end the current frame
		window.display();
	}

	return 0;
}