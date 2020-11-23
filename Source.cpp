#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include<algorithm>
#include"Button.hpp"

//Initial Declarations of SFML components
sf::RenderWindow renderWindow(sf::VideoMode(660, 360), "Arthur- The Gladiator (Level 3)");
sf::Font font;
sf::Event event;
sf::Texture boxTexture, bgTexture;

std::vector<int> randomInts;

//Random Initialization of Numbers
void findRandomInt(int first, int last, std::vector<int>& randomList)
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
	int begin = 20;
	sf::Sprite bgSprite(bgTexture), boxSprite(boxTexture);
	std::vector<std::pair<sf::Sprite, sf::Text>> boxSprites(8);
	bgSprite.scale(1.1f, 1.2f);
	boxSprite.scale(0.05f, 0.05f);
	for (int i = 0; i < boxSprites.size(); i++) {
		boxSprites[i].first = boxSprite;
		boxSprites[i].first.setPosition(begin, 225);

		sf::Text message(std::to_string(randomList[i]), font);
		boxSprites[i].second = message;
		boxSprites[i].second.scale(0.8f, 0.8f);
		boxSprites[i].second.setPosition(begin + 25, 250);
		begin += 80;
	}
	Button newButton(100, 100, 150, 50,
		font, "Start Game",
		sf::Color::Black, sf::Color::Green, sf::Color::Blue);
	//Rendering the Window
	while (renderWindow.isOpen()) {
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();
		}
		renderWindow.clear();
		renderWindow.draw(bgSprite);
		//NEED TO FIND A BETTER WAY
		renderWindow.draw(boxSprites[0].first);
		renderWindow.draw(boxSprites[0].second);
		renderWindow.draw(boxSprites[1].first);
		renderWindow.draw(boxSprites[1].second);
		renderWindow.draw(boxSprites[2].first);
		renderWindow.draw(boxSprites[2].second);
		renderWindow.draw(boxSprites[3].first);
		renderWindow.draw(boxSprites[3].second);
		renderWindow.draw(boxSprites[4].first);
		renderWindow.draw(boxSprites[4].second);
		renderWindow.draw(boxSprites[5].first);
		renderWindow.draw(boxSprites[5].second);
		renderWindow.draw(boxSprites[6].first);
		renderWindow.draw(boxSprites[6].second);
		renderWindow.draw(boxSprites[7].first);
		renderWindow.draw(boxSprites[7].second);
		renderWindow.display();

	}
}



int main()
{
	//Loading the Components
	if (!bgTexture.loadFromFile("images/dungeon.jpg")) {
		std::cout << "Error Displaying Background Image" << std::endl;
	};
	if (!boxTexture.loadFromFile("images/box.png")) {
		std::cout << "Error Displaying Boxes" << std::endl;
	};
	if (!font.loadFromFile("fonts/numberFont.ttf")) {
		std::cout << "Error Displaying Font" << std::endl;
	}

	//Find the random values to be displayed
	findRandomInt(1, 8, randomInts);
	for (int i = 0; i < randomInts.size(); i++)
	{
		std::cout << i+1 << ": " << randomInts[i] << std::endl;
	}

	//Calls the function for rendering
	setVector(randomInts);

	//Sorts the numbers
	std::sort(randomInts.begin(), randomInts.end());
	for (int i = 0; i < randomInts.size(); i++)
	{
		std::cout << randomInts[i] << " ";
	}
}

