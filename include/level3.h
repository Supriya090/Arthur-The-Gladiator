#ifndef LEVEL3_HPP
#define LEVEL3_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Sorting.h"

using namespace std;

class GameLevel3
{
private:
	sf::Font font, openFont;
	sf::Event event;
	sf::Texture bgTexture, boxTexture, princessTexture, openBgTexture, win, ruleTexture;
	sf::Sprite winpage;
	sf::Color color;

	int playerMoves, randomNum, randomNumIndex, flag = 0;
	bool gameWon = 0, noMoves = 0, noEnoughMoves = 0, giveUp = 0, seeRules = 0;
	vector<int> randomList;

	Sorting s1;

public:
	GameLevel3(int);

	void start(sf::RenderWindow &window);
	void setVector(sf::RenderWindow &window);
	void gameOver(sf::RenderWindow &window);
};


#endif