#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "level3.h"

using namespace std;

int playerMoves = 20, randomNum;
//Initial Declarations of SFML components
sf::Font font, openFont;
sf::Event event;
sf::Texture openBgTexture;
sf::RenderWindow renderOpeningWindow(sf::VideoMode(1000, 500), "Arthur- The Gladiator (Level 3)");

//Opening Screen Begins
int main()
{
	if (!openBgTexture.loadFromFile("images/opening.jpg"))
	{
		std::cout << "Error Displaying Background Image" << std::endl;
	};

	if (!openFont.loadFromFile("fonts/ArialCE.ttf"))
	{
		std::cout << "Error Displaying Font" << std::endl;
	}
	sf::Sprite bgSprite(openBgTexture);
	bgSprite.scale(0.7f, 0.35f);
	while (renderOpeningWindow.isOpen())
	{

		while (renderOpeningWindow.pollEvent(event))
		{

			if (event.type == sf::Event::EventType::Closed)
				renderOpeningWindow.close();

			int X = event.mouseButton.x;
			int Y = event.mouseButton.y;

			if (X > 450 && X < 580 && Y > 320 && Y < 370)
			{
				renderOpeningWindow.close();
				GameLevel3 game(playerMoves);
				game.setVector();
			}
		}

		std::vector<std::string> openingInfo(5);
		std::vector<sf::Text> openingInfoText(5);

		sf::Text openingInfo1("Princess is in one of the boxes.", openFont, 20);
		sf::Text openingInfo2("Find the box and press enter to free the princess.", openFont, 20);
		sf::Text openingInfo3("You have " + std::to_string(playerMoves) + " moves remaining. Sorting in either order takes 10 moves.", openFont, 20);
		sf::Text openingInfo4("Click on continue to enter the game.", openFont, 20);

		openingInfo1.setPosition(370, 145);
		openingInfo1.setFillColor(sf::Color::White);

		openingInfo2.setPosition(320, 185);
		openingInfo2.setFillColor(sf::Color::White);

		openingInfo3.setPosition(190, 225);
		openingInfo3.setFillColor(sf::Color::White);

		openingInfo4.setPosition(360, 265);
		openingInfo4.setFillColor(sf::Color::White);

		sf::RectangleShape dSortButton(sf::Vector2f(130, 40));
		dSortButton.setFillColor(sf::Color::White);
		dSortButton.setPosition(sf::Vector2f(450, 320));

		sf::RectangleShape Outline(sf::Vector2f(720, 300));
		Outline.setFillColor(sf::Color::Transparent);
		Outline.setPosition(sf::Vector2f(135, 100));
		Outline.setOutlineThickness(3);
		Outline.setOutlineColor(sf::Color::White);

		sf::Text dSort("Continue", openFont, 20);
		dSort.setPosition(sf::Vector2f(475, 327));
		dSort.setFillColor(sf::Color::Black);

		renderOpeningWindow.clear();
		renderOpeningWindow.draw(bgSprite);

		renderOpeningWindow.draw(openingInfo1);
		renderOpeningWindow.draw(openingInfo2);
		renderOpeningWindow.draw(openingInfo3);
		renderOpeningWindow.draw(openingInfo4);

		renderOpeningWindow.draw(dSortButton);
		renderOpeningWindow.draw(Outline);
		renderOpeningWindow.draw(dSort);
		renderOpeningWindow.display();
	}
}

