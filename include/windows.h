#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "MainMenu.h"
using namespace std;

class gameWindows
{
public:
	gameWindows(string image, sf::RenderWindow &window)
	{

		// sf::RenderWindow window(sf::VideoMode(1000, 900), "---Game Over---");

		sf::Texture gOvertex;
		if (!gOvertex.loadFromFile(image))
		{
			//...
		}

		sf::Sprite gOver;
		gOver.setTexture(gOvertex);
		gOver.setScale(1000 / gOver.getGlobalBounds().width, 900 / gOver.getGlobalBounds().height);

		while (window.isOpen())
		{
			sf::Clock clock;

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}

				else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{

					//tracks the location where mouse button is pressed
					int mouseX = event.mouseButton.x;
					int mouseY = event.mouseButton.y;


					if (mouseX > 600 && mouseX < 850 && mouseY > 554 && mouseY < 692)
					{
						window.close();
					}
					else if (mouseX > 150 && mouseX < 450 && mouseY > 554 && mouseY < 692)
					{
						window.close();
						MainMenu m;
						m.Start();
					}
				}
			}

			if (window.isOpen())
			{
				//window.clear(sf::Color(0,126,3,255));
				window.draw(gOver);
				window.display();
			}

		}
	}


};