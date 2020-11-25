#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <algorithm>

//Initial Declarations of SFML components
sf::Font font, openFont;
sf::Event event;
sf::Texture boxTexture, bgTexture, openBgTexture;
sf::Color color(181, 101, 29);
sf::RenderWindow renderWindow(sf::VideoMode(1000, 900), "Arthur- The Gladiator (Level 3)");

std::vector<int> randomInts;
int playerMoves = 20, randomNum = rand()%40 + 1, randomNumIndex, flag = 0;
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

		sf::RectangleShape Outline(sf::Vector2f(750, 250));
		Outline.setFillColor(sf::Color::Transparent);
		Outline.setPosition(sf::Vector2f(135, 170));
		Outline.setOutlineThickness(3);
		Outline.setOutlineColor(sf::Color::White);

		sf::Text dSort("Continue", openFont, 20);
		dSort.setPosition(sf::Vector2f(475, 356));
		dSort.setFillColor(sf::Color::Black);
		
		renderOpeningWindow.clear();
		renderOpeningWindow.draw(bgSprite);

		renderOpeningWindow.draw(openingInfo1);
		renderOpeningWindow.draw(openingInfo2);
		renderOpeningWindow.draw(openingInfo3);
		
		renderOpeningWindow.draw(dSortButton);
		renderOpeningWindow.draw(Outline);
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
	//sf::RenderWindow renderWindow(sf::VideoMode(1000, 900), "Arthur- The Gladiator (Level 3)");
	sf::RectangleShape selectSquare(sf::Vector2f(85, 85));
	selectSquare.setFillColor(sf::Color::Transparent);
	selectSquare.setOutlineColor(sf::Color::White);
	selectSquare.setOutlineThickness(3);
	selectSquare.setPosition(10, 195);
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

				if (X > 470 && X < 730 && Y > 50 && Y < 80)
				{
					//sort in ascending order
					std::sort(randomList.begin(), randomList.end());
					flag = 1;
					playerMoves -= 10;
					if (playerMoves < 0)	gameOver();
				}

				if (X > 730 && X < 985 && Y > 50 && Y < 80)
				{
					//sort in descending order
					std::sort(randomList.begin(), randomList.end(), std::greater<int>());
					flag = -1;
					playerMoves -= 10;
					if (playerMoves < 0)	gameOver();
				}
			}

			if (event.type == sf::Event::EventType::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
				{
					if (selectSquare.getPosition().x == 10)
					{
						if (selectSquare.getPosition().y == 195)
						{
							selectSquare.setPosition(10, selectSquare.getPosition().y);
						}
						else
						{
							selectSquare.setPosition(910, selectSquare.getPosition().y - 140);
							playerMoves += 1;
						}
					}
					else
					{
						selectSquare.move(-100.f, 0.f);
						playerMoves += 1;
					}
					std::cout << "Left" << std::endl;
					break;
				}

				case sf::Keyboard::Right:
				{
					if (selectSquare.getPosition().x > 900)
					{
						if (selectSquare.getPosition().y == (195+3*140))
						{
							
							selectSquare.setPosition(910, selectSquare.getPosition().y);
						}
						else
						{
							selectSquare.setPosition(10, selectSquare.getPosition().y + 140);
							playerMoves -= 1;
						}
					}
					else
					{
						selectSquare.move(100.f, 0.f);
						playerMoves -= 1;
					}
					if (playerMoves < 0)	gameOver();
					std::cout << "Right" << std::endl;
					std::cout << selectSquare.getPosition().x << " "<<selectSquare.getPosition().y<< std::endl;
					break;
				}

				case sf::Keyboard::Enter:
				{
					int xPos = selectSquare.getPosition().x;
					int yPos = selectSquare.getPosition().y;
					if (flag == 1)	randomNumIndex = randomNum;
					if (flag == -1)	randomNumIndex = 41 - randomNum;
					if (randomNumIndex / 10 == 0)
					{
						if (xPos > (randomNumIndex - 1) * 100 && xPos < (randomNumIndex * 100 - 50) && yPos == 195)
						{
							std::cout << "Princess is here" << std::endl;
						}
					}
					else
					{
						if (xPos > (randomNumIndex%10 - 1) * 100 && xPos < ((randomNumIndex%10) * 100 - 50) && yPos == (randomNumIndex / 10)*140 + 195)
						{
							std::cout << "Princess is here" << std::endl;
						}
					}
					std::cout << "Enter" << std::endl;
					break;
				}

				case sf::Keyboard::Down:
				{
					std::cout << "Down" << std::endl;
					break;
				}
				}
			}
		}

		sf::Sprite bgSprite(bgTexture), boxSprite(boxTexture);
		std::vector<std::pair<sf::Sprite, sf::Text>> boxSprites(40);

		bgSprite.scale(2.0f, 3.0f);
		boxSprite.scale(0.06f, 0.06f);

		sf::RectangleShape dSortButton(sf::Vector2f(250, 30));
		dSortButton.setFillColor(color);
		dSortButton.setPosition(sf::Vector2f(475, 50));

		sf::RectangleShape aSortButton(sf::Vector2f(250, 30));
		aSortButton.setFillColor(color);
		aSortButton.setPosition(sf::Vector2f(735, 50));

		sf::RectangleShape movesButton(sf::Vector2f(120, 30));
		movesButton.setFillColor(color);
		movesButton.setPosition(sf::Vector2f(865, 100));


		sf::Text aSort("Sort in Descending Order", font, 16);
		aSort.setPosition(sf::Vector2f(750, 55));
		aSort.setFillColor(sf::Color::White);

		sf::Text dSort("Sort in Ascending Order", font, 16);
		dSort.setPosition(sf::Vector2f(495, 55));
		dSort.setFillColor(sf::Color::White);

		sf::Text movesText("Moves: ", font, 16);
		movesText.setPosition(sf::Vector2f(880, 105));
		movesText.setFillColor(sf::Color::White);

		sf::Text playerMovesText(std::to_string(playerMoves), font, 16);
		playerMovesText.setPosition(sf::Vector2f(950, 105));
		playerMovesText.setFillColor(sf::Color::White);

		int coordY = 200;
		int a = 0;
		for (int j = 0; j < 4; j++)
		{
			int coordX = 15;
			for (int i = 0; i < boxSprites.size() / 4; i++)
			{
				boxSprites[a].first = boxSprite;
				boxSprites[a].first.setPosition(coordX, coordY);

				sf::Text message(std::to_string(randomList[a]), font);
				boxSprites[a].second = message;
				boxSprites[a].second.scale(0.8f, 0.8f);
				boxSprites[a].second.setPosition(coordX + 25, coordY + 35);
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
		renderWindow.draw(selectSquare);
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
	if (!font.loadFromFile("fonts/test.ttf"))
	{
		std::cout << "Error Displaying Font" << std::endl;
	}

	//Find the random values to be displayed
	findRandomInt(1, 40, randomInts);
	for (int i = 0; i < randomInts.size(); i++)
	{
		std::cout << i + 1 << ": " << randomInts[i] << std::endl;
		if (randomInts[i] == randomNum)	randomNumIndex = i + 1;
	}
	std::cout << "Random number "<<randomNum<<" is at index " << randomNumIndex<< std::endl;
	//Calls the function for rendering
	//openingWindow();
	setVector(randomInts);
}

void gameOver()
{
	//sf::RenderWindow renderWindow(sf::VideoMode(1000, 900), "Arthur- The Gladiator (Level 3)");
	std::cout << "You are out of moves. Game Over!" << std::endl;
	renderWindow.close();
}