#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"

Player::Player() //Constructor
{

}

void Player::pSprite(sf::Texture& texPlayer) //Overload Constructor
{
	//PLAYER SPRITE
	sprite.setTexture(texPlayer); //Set Sprite Texture
	sprite.setPosition(posX * 30 - 15, posY * 30 - 15); //Set Sprite Position (Centre)
	// sprite.setScale(1f, 1.5f); //Sprite Scale
	sf::Vector2i face(1, Down); //Default Sprite Sheet Crop
	sprite.setTextureRect(sf::IntRect(face.x * 50, face.y * 50, 50, 50)); //Crop Sprite Sheet (Default Crop)

	//PLAYER / ANIMATION SPEED
	animationTime = sf::milliseconds(1000); //Animation Speed
	speed = 0.20; //Player Speed
}

Player::~Player() //Destructor
{
}

//ACCESSOR FUNCTIONS
sf::Sprite Player::getSprite() const //Player Sprite
{
	return sprite;
}

void Player::updatePos()
{
	sprite.setPosition(posX * 30 - 10, posY * 30 - 15);
}

//PLAYER MOVEMENT
void Player::moveUp()
{
	face.y = Up; //Set 'face.y' Equal To 'Up' (_Direction Enum)
	sprite.move(0, -speed); //Move Player Sprite

	if (animationClock.getElapsedTime() > animationTime)
	{
		sprite.setTextureRect(sf::IntRect(face.x * 50, face.y * 50, 50, 50)); //Crop Sprite Sheet

		//Animation
		face.x++;
		if (face.x * 50 >= sprite.getTexture()->getSize().x)
		{
			face.x = 0;
		}
		animationClock.restart();

	}
	posY--;
	updatePos();

}

void Player::moveDown()
{
	face.y = Down; //Set 'face.y' Equal To 'Up' (_Direction Enum)
	sprite.move(0, speed); //Move Player Sprite

	if (animationClock.getElapsedTime() > animationTime)
	{
		sprite.setTextureRect(sf::IntRect(face.x * 50, face.y * 50, 50, 50)); //Crop Sprite Sheet

		//Animation
		face.x++;
		if (face.x * 50 >= sprite.getTexture()->getSize().x)
		{
			face.x = 0;
		}sprite.setPosition(posX * 30 - 10, posY * 30 - 10);
		animationClock.restart();

	}
	posY++;
	updatePos();
}

void Player::moveRight()
{
	face.y = Right; //Set 'face.y' Equal To 'Up' (_Direction Enum)
	sprite.move(speed, 0); //Move Player Sprite

	if (animationClock.getElapsedTime() > animationTime)
	{
		sprite.setTextureRect(sf::IntRect(face.x * 50, face.y * 50, 50, 50)); //Crop Sprite Sheet

		//Animation
		face.x++;
		if (face.x * 50 >= sprite.getTexture()->getSize().x)
		{
			face.x = 0;
		}
		animationClock.restart();
	}
	posX++;
	updatePos();
}


void Player::moveLeft()
{
	face.y = Left; //Set 'face.y' Equal To 'Up' (_Direction Enum)
	sprite.move(-speed, 0); //Move Player Sprite

	if (animationClock.getElapsedTime() > animationTime)
	{
		sprite.setTextureRect(sf::IntRect(face.x * 50, face.y * 50, 50, 50)); //Crop Sprite Sheet

		//Animation
		face.x++;
		if (face.x * 50 >= sprite.getTexture()->getSize().x)
		{
			face.x = 0;
		}
		animationClock.restart();
	}
	posX--;
	updatePos();
}

void Player::setSpeed(float TEMP_Speed, sf::Time TEMP__AnimTime) //Sprint Speed
{
	speed = TEMP_Speed;
	animationTime = TEMP__AnimTime;
}
