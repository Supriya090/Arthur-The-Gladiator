//
// Created by Hyphen on 2/18/2020.
//
#include "game.h"
#include "MainMenu.h"
#include <iostream>
#include "level3.h"


MainMenu::MainMenu()

{
	window1.create(sf::VideoMode(1000, 900), "Arthur-The Gradiator", sf::Style::Default);
	selectedIndex = 0,
		isPressedUp = false;
	isPressedDown = false;
	isPressedEnter = false;


	texbg.loadFromFile("media/start.jpg");
	bg.setTexture(texbg);
	bg.setScale(0.63f, 1.0f);
}

void MainMenu::Start()
{
	while (window1.isOpen())
	{
		sf::Event event{};
		while (window1.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				playerInput(event.key.code, true);
				break;


			case sf::Event::KeyReleased:
				playerInput(event.key.code, false);
				break;
			case sf::Event::Closed:
				window1.close();
				break;
			}
		}
		drawMenu();
	}
}

void MainMenu::drawMenu()
{

	sf::Text menu[5];
	if (!font.loadFromFile("arial.ttf")) {
		// handle error
	}

	menu[0].setString(" Play");
	menu[0].setPosition(sf::Vector2f(449, 600));

	menu[1].setString(" Rules");
	menu[1].setPosition(sf::Vector2f(445, 700));

	menu[2].setString(" Exit");
	menu[2].setPosition(sf::Vector2f(449, 800));


	for (int j = 0; j < 5; j++)
	{
		menu[j].setFont(font);
		menu[j].setStyle(sf::Text::Bold);
		menu[j].setCharacterSize(25);
		menu[j].setFillColor(sf::Color::Black);
	}
	window1.clear(sf::Color::White);
	window1.draw(bg);
	for (int i = 0; i < 5; i++)
	{
		menu[i].setFillColor(i == selectedIndex ? sf::Color::Red : sf::Color::Black);
		window1.draw(menu[i]);
	}
	window1.display();

}

void MainMenu::playerInput(sf::Keyboard::Key & key, bool isPressed)
{
	switch (key) {
	case sf::Keyboard::Up:
		isPressedUp = isPressed;
		break;
	case sf::Keyboard::Down:
		isPressedDown = isPressed;
		break;
	case sf::Keyboard::Return:
		isPressedEnter = isPressed;
		break;

	default:
		break;
	}
	if (isPressedUp)
		MoveUp(true);
	if (isPressedDown)
		MoveUp(false);
	if (isPressedEnter)
		GetPressed();
}

void MainMenu::MoveUp(bool up = true)
{
	if (up and selectedIndex >= 0) selectedIndex--;
	else if (not up and selectedIndex != 2) selectedIndex++;
}
void MainMenu::GetPressed()
{
	switch (selectedIndex)
	{
	case(1):
		window1.close();
		break;
	case(2):
		exit(0);
	case(0):
		//GameLevel3 l3(30);

		level2 l2(30,2);
		l2.start();
		//game game;
		//game.start();
		break;

	}
}

void MainMenu::Intro()
{

	sf::Texture tex[4];
	//Load the images for introduction
	tex[0].loadFromFile("media/1.jpg");
	tex[1].loadFromFile("media/2.jpg");
	tex[2].loadFromFile("media/3.jpg");
	tex[3].loadFromFile("media/4.jpg");

	sf::Sprite sprite[4];

	for (int i = 0; i < 4; i++)
	{
		sprite[i].setTexture(tex[i]);
	}



	//draw the images one by one
	for (int i = 0; i < 4; i++)
	{
		//Clears the window
		window1.clear();
		window1.draw(sprite[i]);
		window1.display();
		//put on sleep for 4 seconds
		sf::sleep(sf::seconds(4));
	}
	window1.close();
	game game;
	game.start();

}

MainMenu::~MainMenu()
= default;