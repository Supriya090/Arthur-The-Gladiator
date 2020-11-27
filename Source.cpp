#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include<time.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono_literals;

//Initial Declarations of SFML components
sf::Font font, openFont;
sf::Event event;
sf::Texture boxTexture, bgTexture, openBgTexture, princessTexture;
sf::Color color(181, 101, 29);
sf::RenderWindow renderWindow(sf::VideoMode(1000, 900), "Arthur- The Gladiator (Level 3)");

std::vector<int> randomInts;
int playerMoves = 20, randomNum, randomNumIndex, flag = 0;
bool gameWon = 0, noMoves = 0, noEnoughMoves = 0, giveUp = 0;
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

//Merge Sort - Ascending
void merge(vector<int> &randomInts, int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays
	vector<int> L(n1), R(n2);

	// Copy data to temp arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i] = randomInts[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = randomInts[m + 1 + j];

	// Merge the temp arrays back into arr[l..r]

	// Initial index of first subarray
	int i = 0;

	// Initial index of second subarray
	int j = 0;

	// Initial index of merged subarray
	int k = l;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			randomInts[k] = L[i];
			i++;
		}
		else
		{
			randomInts[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of
	// L[], if there are any
	while (i < n1)
	{
		randomInts[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of
	// R[], if there are any
	while (j < n2)
	{
		randomInts[k] = R[j];
		j++;
		k++;
	}
}

// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(vector<int> &randomInts, int l, int r)
{
	if (l >= r)
	{
		return; //returns recursively
	}
	int m = (l + r - 1) / 2;
	mergeSort(randomInts, l, m);
	mergeSort(randomInts, m + 1, r);
	merge(randomInts, l, m, r);
}
//End Ascending Sort

//Quick Sort - Descending
void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(vector<int> &randomInts, int low, int high)
{
	int pivot = randomInts[high]; // pivot
	int i = (low - 1);            // Index of smaller element

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot
		if (randomInts[j] > pivot)
		{
			i++; // increment index of smaller element
			swap(&randomInts[i], &randomInts[j]);
		}
	}
	swap(&randomInts[i + 1], &randomInts[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(vector<int> &randomInts, int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(randomInts, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(randomInts, low, pi - 1);
		quickSort(randomInts, pi + 1, high);
	}
}
//End Descending Sort

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

	sf::Sprite princessSprite(princessTexture);
	princessSprite.setTextureRect(sf::IntRect(30, 30, 80, 130));
	princessSprite.setScale(0.35f, 0.35f);
	princessSprite.setPosition(300, 300);

	//Rendering the Window
	while (renderWindow.isOpen())
	{
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();
			if (playerMoves <= 0)
			{
				noMoves = 1;
			}
			if (event.type == sf::Event::EventType::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				int X = event.mouseButton.x;
				int Y = event.mouseButton.y;
				if (playerMoves >= 10)
				{
					if (X > 470 && X < 730 && Y > 50 && Y < 80)
					{
						//sort in ascending order
						mergeSort(randomList, 0, randomList.size() - 1);
						flag = 1;
						playerMoves -= 10;
					}

					if (X > 730 && X < 985 && Y > 50 && Y < 80)
					{
						//sort in descending order
						quickSort(randomList, 0, randomList.size() - 1);
						flag = -1;
						playerMoves -= 10;
					}
				}
				else
				{
					noEnoughMoves = 1;
				}
				if (X > 50 && X < 180 && Y>50 && Y < 80)
				{
					giveUp = 1;
					noEnoughMoves = 0;
				}
			}

			if (event.type == sf::Event::EventType::KeyPressed)
			{
				noEnoughMoves = 0;
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
				{
					if (playerMoves > 0)
					{
						if (selectSquare.getPosition().x == 10)
						{
							if (selectSquare.getPosition().y == 195)
							{
								//selectSquare.setPosition(10, selectSquare.getPosition().y);
								selectSquare.setPosition(910, 195 + 3 * 140);
							}
							else
							{
								selectSquare.setPosition(910, selectSquare.getPosition().y - 140);
								playerMoves -= 1;
							}
						}
						else
						{
							selectSquare.move(-100.f, 0.f);
							playerMoves -= 1;
						}
					}
					std::cout << "Left" << std::endl;
					break;
				}

				case sf::Keyboard::Right:
				{
					if (playerMoves > 0)
					{
						if (selectSquare.getPosition().x > 900)
						{
							if (selectSquare.getPosition().y == (195 + 3 * 140))
							{
								//selectSquare.setPosition(910, selectSquare.getPosition().y);
								selectSquare.setPosition(10, 195);
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
					}
					//if (playerMoves < 0)	gameOver();
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
					int remVal = randomNumIndex % 10;
					int divVal = randomNumIndex / 10;
					if (remVal == 0)
					{
						remVal = 10;
						divVal--;
					}
					princessSprite.setPosition((remVal) * 100 - 70, (divVal) * 140 + 215);
					if (playerMoves >= 0)
					{
						if (divVal == 0)
						{
							if (xPos > (randomNumIndex - 1) * 100 && xPos < (randomNumIndex * 100 - 50) && yPos == 195)
							{
								gameWon = 1;
								std::cout << "Princess is here" << std::endl;
								princessSprite.move(0, -65);
							}
						}
						else
						{
							if (xPos > (remVal - 1) * 100 && xPos < ((remVal) * 100 - 50) && yPos == (divVal) * 140 + 195)
							{
								gameWon = 1;
								std::cout << "Princess is here" << std::endl;
								std::cout << princessSprite.getPosition().y << std::endl;
								princessSprite.move(0, -65);
								//gameOver();
							}
						}
						std::cout << gameWon << std::endl;
						playerMoves--;
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
		dSortButton.setOutlineThickness(2);
		dSortButton.setOutlineColor(sf::Color::White);

		sf::RectangleShape aSortButton(sf::Vector2f(250, 30));
		aSortButton.setFillColor(color);
		aSortButton.setPosition(sf::Vector2f(735, 50));
		aSortButton.setOutlineThickness(2);
		aSortButton.setOutlineColor(sf::Color::White);

		sf::RectangleShape movesButton(sf::Vector2f(120, 30));
		movesButton.setFillColor(color);
		movesButton.setPosition(sf::Vector2f(865, 100));

		sf::RectangleShape giveUpButton(sf::Vector2f(120, 30));
		giveUpButton.setFillColor(color);
		giveUpButton.setPosition(sf::Vector2f(50, 50));
		giveUpButton.setOutlineThickness(2);
		giveUpButton.setOutlineColor(sf::Color::White);

		sf::RectangleShape princessInfoBox(sf::Vector2f(230, 30));
		princessInfoBox.setFillColor(color);
		princessInfoBox.setPosition(sf::Vector2f(625, 100));

		sf::RectangleShape congratulationsBox(sf::Vector2f(650, 150));
		congratulationsBox.setFillColor(color);
		congratulationsBox.setPosition(175, 360);

		sf::RectangleShape congratulationsBorder(sf::Vector2f(610, 110));
		congratulationsBorder.setFillColor(sf::Color::Transparent);
		congratulationsBorder.setPosition(sf::Vector2f(195, 380));
		congratulationsBorder.setOutlineThickness(3);
		congratulationsBorder.setOutlineColor(sf::Color::White);

		sf::Text princessInfoText("Princess is in Box No. " + std::to_string(randomNum), font, 16);
		princessInfoText.setFillColor(sf::Color::White);
		princessInfoText.setPosition(sf::Vector2f(640, 105));

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

		sf::Text giveUpButtonText("Give Up", font, 16);
		giveUpButtonText.setPosition(sf::Vector2f(75, 55));
		giveUpButtonText.setFillColor(sf::Color::White);

		sf::Text congratulationsText("Congratulations! You won with " + std::to_string(playerMoves) + " moves remaining!", font, 20);
		congratulationsText.setFillColor(sf::Color::White);
		congratulationsText.setPosition(sf::Vector2f(225, 420));

		sf::Text sorryText("Sorry, you are out of moves. Game Over!", font, 20);
		sorryText.setFillColor(sf::Color::White);
		sorryText.setPosition(sf::Vector2f(275, 420));

		sf::Text noEnoughMovesText1("You don't have enough moves for sorting!", font, 20);
		noEnoughMovesText1.setFillColor(sf::Color::White);
		noEnoughMovesText1.setPosition(sf::Vector2f(275, 405));

		sf::Text noEnoughMovesText2("Use the remaining moves elsewhere or give up!", font, 20);
		noEnoughMovesText2.setFillColor(sf::Color::White);
		noEnoughMovesText2.setPosition(sf::Vector2f(250, 435));

		sf::Text giveUpText("You gave up with " + std::to_string(playerMoves) + " moves remaining!", font, 20);
		giveUpText.setFillColor(sf::Color::White);
		giveUpText.setPosition(sf::Vector2f(285, 420));

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

		//if (gameWon) 
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
		renderWindow.draw(giveUpButton);
		renderWindow.draw(giveUpButtonText);
		renderWindow.draw(princessInfoBox);
		renderWindow.draw(princessInfoText);
		renderWindow.draw(playerMovesText);
		renderWindow.draw(selectSquare);
		if (noMoves || gameWon || noEnoughMoves || giveUp)
		{
			if (gameWon)
			{
				renderWindow.draw(princessSprite);
			}
			renderWindow.draw(congratulationsBox);
			renderWindow.draw(congratulationsBorder);
			if (noMoves)
			{
				renderWindow.draw(sorryText);
			}
			if (gameWon)
			{
				renderWindow.draw(congratulationsText);
			}
			if (noEnoughMoves)
			{
				renderWindow.draw(noEnoughMovesText1);
				renderWindow.draw(noEnoughMovesText2);
			}
			if (giveUp)
			{
				renderWindow.draw(giveUpText);
			}
		}
		renderWindow.display();
		if (gameWon || noMoves || giveUp)
		{
			gameOver();
		}
	}
}

int main()
{
	srand(time(NULL));
	randomNum = rand() % 40 + 1;
	//Loading the Components
	if (!bgTexture.loadFromFile("images/dungeon.jpg"))
	{
		std::cout << "Error Displaying Background Image" << std::endl;
	};
	if (!boxTexture.loadFromFile("images/box.png"))
	{
		std::cout << "Error Displaying Boxes" << std::endl;
	};
	if (!font.loadFromFile("fonts/mainFont.ttf"))
	{
		std::cout << "Error Displaying Font" << std::endl;
	}
	if (!princessTexture.loadFromFile("images/princess.png", sf::IntRect(0, 0, 110, 170)))
	{
		std::cout << "Error displaying Princess Image" << std::endl;
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
	openingWindow();
	setVector(randomInts);
}

void gameOver()
{
	if (noMoves)
	{
		std::cout << "You are out of moves. Game Over!" << std::endl;
	}
	if (gameWon)
	{
		std::cout << "Congratulations! You won with " << playerMoves << " moves remaining!" << std::endl;
	}
	if (giveUp)
	{
		std::cout << "You gave up with " << playerMoves << " moves remaining!" << std::endl;
	}
	std::this_thread::sleep_for(1.5s);
	renderWindow.close();
}