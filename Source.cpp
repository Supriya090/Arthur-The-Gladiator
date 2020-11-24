#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <algorithm>

//Initial Declarations of SFML components
sf::Font font, openFont;
sf::Event event;
sf::Texture boxTexture, bgTexture, openBgTexture;

std::vector<int> randomInts;
int playerMoves = 20, randomNum = rand()%40 + 1;
void gameOver();
void setVector(std::vector<int>);

//Opening Screen Begins
void openingWindow()
{
	sf::RenderWindow renderOpeningWindow(sf::VideoMode(1000, 500), "Arthur- The Gladiator (Level 3)");
	if (!openBgTexture.loadFromFile("images/opening.jpg"))
	{
		std::cout << "Error Displaying Background Image" << std::endl;
	};
	
	if (!openFont.loadFromFile("fonts/ArialCE.ttf"))
	{
		std::cout << "Error Displaying Font" << std::endl;
	}
	sf::Sprite bgSprite(openBgTexture);
	bgSprite.scale(2.0f, 1.5f);
	while (renderOpeningWindow.isOpen())
	{

		while (renderOpeningWindow.pollEvent(event))
		{

			if (event.type == sf::Event::EventType::Closed)
				renderOpeningWindow.close();

			int X = event.mouseButton.x;
			int Y = event.mouseButton.y;

			if (X > 450 && X < 580 && Y > 350 && Y < 390)
			{
				renderOpeningWindow.close();
				setVector(randomInts);
			}
		}

		std::vector<std::string> openingInfo(5);
		std::vector<sf::Text> openingInfoText(5);

		sf::Text openingInfo1("Princess is in Box No. " + std::to_string(randomNum), openFont, 20);
		sf::Text openingInfo2("You have " + std::to_string(playerMoves) + " moves remaining.", openFont , 20);
		sf::Text openingInfo3("Sorting in either order takes 10 moves. Press continue to enter the game.", openFont, 20);
		
		openingInfo1.setPosition(410, 200);
		openingInfo1.setFillColor(sf::Color::White);

		openingInfo2.setPosition(380, 240);
		openingInfo2.setFillColor(sf::Color::White);

		openingInfo3.setPosition(180, 285);
		openingInfo3.setFillColor(sf::Color::White);

		sf::RectangleShape dSortButton(sf::Vector2f(130, 40));
		dSortButton.setFillColor(sf::Color::White);
		dSortButton.setPosition(sf::Vector2f(450, 350));

		sf::RectangleShape Horizontal1(sf::Vector2f(750, 3));
		Horizontal1.setFillColor(sf::Color::White);
		Horizontal1.setPosition(sf::Vector2f(135, 170));

		sf::RectangleShape Vertical1(sf::Vector2f(3, 250));
		Vertical1.setFillColor(sf::Color::White);
		Vertical1.setPosition(sf::Vector2f(135, 170));

		sf::RectangleShape Horizontal2(sf::Vector2f(750, 3));
		Horizontal2.setFillColor(sf::Color::White);
		Horizontal2.setPosition(sf::Vector2f(135, 420));

		sf::RectangleShape Vertical2(sf::Vector2f(3, 250));
		Vertical2.setFillColor(sf::Color::White);
		Vertical2.setPosition(sf::Vector2f(885, 170));

		sf::Text dSort("Continue", openFont, 20);
		dSort.setPosition(sf::Vector2f(475, 356));
		dSort.setFillColor(sf::Color::Black);
		
		renderOpeningWindow.clear();
		renderOpeningWindow.draw(bgSprite);

		renderOpeningWindow.draw(openingInfo1);
		renderOpeningWindow.draw(openingInfo2);
		renderOpeningWindow.draw(openingInfo3);
		
		renderOpeningWindow.draw(dSortButton);
		renderOpeningWindow.draw(Horizontal1);
		renderOpeningWindow.draw(Vertical1);
		renderOpeningWindow.draw(Horizontal2);
		renderOpeningWindow.draw(Vertical2);
		renderOpeningWindow.draw(dSort);
		renderOpeningWindow.display();
	}
}
//Opening Screen Ends


//MAIN SCREEN

//Random Initialization of Numbers
void findRandomInt(int first, int last, std::vector<int> &randomList)
{
	for (int i = first; i <= last; i++)
	{
		randomList.push_back(i);
	}
	int swapIndex;
	for (int i = 0; i < randomList.size(); i++)
	{
		std::cout << rand() << std::endl;
		swapIndex = rand() % randomList.size();
		std::swap(randomList[i], randomList[swapIndex]);
	}
}

//Creating the Vector Pair of Boxes and Numbers
void setVector(std::vector<int> randomList)
{
	sf::RenderWindow renderWindow(sf::VideoMode(1000, 900), "Arthur- The Gladiator (Level 3)");
	//Rendering the Window
	while (renderWindow.isOpen())
	{

		while (renderWindow.pollEvent(event))
		{

			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();

			if (event.type == sf::Event::EventType::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				int X = event.mouseButton.x;
				int Y = event.mouseButton.y;

				if (X > 490 && X < 750 && Y > 30 && Y < 60)
				{
					//sort in ascending order
					std::sort(randomList.begin(), randomList.end());
					if (playerMoves < 10)
						std::cout << "You don't have enough moves to sort! Forfeit if you " << std::endl;
					playerMoves -= 10;
					if (playerMoves < 0)	gameOver();
				}

				if (X > 750 && X < 1000 && Y > 30 && Y < 60)
				{
					//sort in descending order
					std::sort(randomList.begin(), randomList.end(), std::greater<int>());
					playerMoves -= 10;
					if (playerMoves <= 0)	gameOver();
				}
			}
		}

		sf::Sprite bgSprite(bgTexture), boxSprite(boxTexture);
		std::vector<std::pair<sf::Sprite, sf::Text>> boxSprites(40);

		bgSprite.scale(2.0f, 3.0f);
		boxSprite.scale(0.07f, 0.07f);

		sf::RectangleShape dSortButton(sf::Vector2f(250, 30));
		dSortButton.setFillColor(sf::Color::Green);
		dSortButton.setPosition(sf::Vector2f(490, 30));

		sf::RectangleShape aSortButton(sf::Vector2f(250, 30));
		aSortButton.setFillColor(sf::Color::Green);
		aSortButton.setPosition(sf::Vector2f(750, 30));

		sf::CircleShape movesButton(40);
		movesButton.setFillColor(sf::Color::Green);
		movesButton.setPosition(sf::Vector2f(750, 80));

		sf::Text aSort("Sort in Descending order", font, 20);
		aSort.setPosition(sf::Vector2f(775, 35));
		aSort.setFillColor(sf::Color::Black);

		sf::Text dSort("Sort in Ascending order", font, 20);
		dSort.setPosition(sf::Vector2f(515, 35));
		dSort.setFillColor(sf::Color::Black);

		sf::Text movesText("Moves", font, 20);
		movesText.setPosition(sf::Vector2f(775, 90));
		movesText.setFillColor(sf::Color::Black);

		sf::Text playerMovesText(std::to_string(playerMoves), font, 20);
		playerMovesText.setPosition(sf::Vector2f(775, 100));
		playerMovesText.setFillColor(sf::Color::Black);

		int coordY = 200;
		int a = 0;
		for (int j = 0; j < 4; j++)
		{
			int coordX = 20;
			for (int i = 0; i < boxSprites.size() / 4; i++)
			{
				boxSprites[a].first = boxSprite;
				boxSprites[a].first.setPosition(coordX, coordY);

				sf::Text message(std::to_string(randomList[a]), font);
				boxSprites[a].second = message;
				boxSprites[a].second.scale(0.8f, 0.8f);
				boxSprites[a].second.setPosition(coordX + 35, coordY + 35);
				coordX += 100;
				a++;
			}
			coordY += 140;
		}
		renderWindow.clear();
		renderWindow.draw(bgSprite);

		//drawing the boxes
		for (int i = 0; i < 40; i++)
		{
			renderWindow.draw(boxSprites[i].first);
			renderWindow.draw(boxSprites[i].second);
		}
		renderWindow.draw(dSortButton);
		renderWindow.draw(aSortButton);
		renderWindow.draw(dSort);
		renderWindow.draw(aSort);
		renderWindow.draw(movesButton);
		renderWindow.draw(movesText);
		renderWindow.draw(playerMovesText);
		renderWindow.display();
	}
}

int main()
{
	//Loading the Components
	if (!bgTexture.loadFromFile("images/dungeon.jpg"))
	{
		std::cout << "Error Displaying Background Image" << std::endl;
	};
	if (!boxTexture.loadFromFile("images/box.png"))
	{
		std::cout << "Error Displaying Boxes" << std::endl;
	};
	if (!font.loadFromFile("fonts/numberFont.ttf"))
	{
		std::cout << "Error Displaying Font" << std::endl;
	}

	//Find the random values to be displayed
	findRandomInt(1, 40, randomInts);
	for (int i = 0; i < randomInts.size(); i++)
	{
		std::cout << i + 1 << ": " << randomInts[i] << std::endl;
	}

	//Calls the function for rendering
	openingWindow();
	//setVector(randomInts);
}

void gameOver()
{
	sf::RenderWindow renderWindow(sf::VideoMode(1000, 900), "Arthur- The Gladiator (Level 3)");
	std::cout << "You are out of moves. Game Over!" << std::endl;
	renderWindow.close();
}