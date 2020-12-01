#include<SFML/Graphics.hpp>

class Player
{
public:
	Player(); //Constructor
	void pSprite(sf::Texture&); //Overload Constructor
	~Player(); //Destructor

	//PLAYER MOVEMENT FUNCTIONS
	void updatePos();
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void setSpeed(float, sf::Time);

	//ACCESSOR FUNCTIONS
	sf::Sprite getSprite() const;

private:
	int posX = 2, posY = 2;
	sf::Sprite sprite; //Declare Player Sprite
	sf::Vector2i face; //Declare Source (Sprite Sheet Crop)
	enum _Direction { Down, Left, Right, Up }; //Declare Direction Enumeration

	//ANIMATION DATA
	float speed; //Player Speed
	sf::Clock animationClock; //Player Animation Clock
	sf::Time animationTime; //Player Animation Time
};

