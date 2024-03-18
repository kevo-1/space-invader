#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"
class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imagecount, float switchtime , float speed);

public: 
	void update(float dt);
	void draw(sf::RenderWindow& window);
	sf::Vector2f position();
	sf::Vector2f size();
	bool collision(sf::RectangleShape enemy);
	bool collision1(sf::Sprite enemy);

private:
	sf::RectangleShape character;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceleft;

};

