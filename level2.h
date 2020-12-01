#pragma once
#include "SFML/Graphics.hpp"
#include<iostream>

#include<functional>
#include<math.h>
#include<float.h>
#include<vector>
#include<set>
#include<string.h>
#include<string>
#include<sstream>

#include "level3.h"
#include "bfs.h"

using namespace std;
#define N 12

class level2
{
public:
	level2();
	level2(int move, int lfe);
	~level2() {//...
	}


	void start();
	void valid(int x, int y);
	void reset(int x, int y);
	void nextlevel();
	void startGame();
	//drawing chessboard size 8*8
	sf::RectangleShape tileMap[N][N];

private:
	sf::Font fonts;
	sf::Texture texknight, texprincess, texback, rulesTexture;
	sf::Sprite knight, princess, background, rulesSprite;
	float gridSizef = 900 / N;

	int posX = 0, posY = 0, destX, destY;
	float hintX, hintY;
	int moves, score, life;
	bool seeRules = 0;
	bfs bf;

};

