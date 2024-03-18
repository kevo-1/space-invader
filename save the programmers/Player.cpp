#include "Player.h"
Player::Player(sf::Texture* texture, sf::Vector2u imagecount, float switchtime, float speed):
	animation(texture , imagecount , switchtime)
{
	this->speed = speed;
	row = 0;
	faceleft = true;
	character.setSize(sf::Vector2f(131.0f, 131.0f));
	character.setPosition(348.8, 764);
	character.setTexture(texture);
}

void movesx(sf::RectangleShape& shape) {
	if (shape.getPosition().x <= -10)
		shape.setPosition(-10, shape.getPosition().y);
	if (shape.getPosition().x >= 800 - 120)
		shape.setPosition(800 -  120, shape.getPosition().y);
}

void movesy(sf::RectangleShape& shape) {
	if (shape.getPosition().y <= -5)
		shape.setPosition(shape.getPosition().x, -5);
	if (shape.getPosition().y >= 900 - 100)
		shape.setPosition(shape.getPosition().x, 900 - 100);
}

void Player::update(float dt) 
{
	sf::Vector2f moving(0.0f, 0.0f);
	//left :
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        moving.x -= speed * dt;
		movesx(character);
    }
    //right :
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        moving.x += speed * dt;
		movesx(character);
    }

	if (moving.x == 0.0f)
		row = 0;
	else 
	{
		row = 2;
		if (moving.x > 0.0f) {
			faceleft = false;
		}
		else {
			faceleft = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		moving.y -= speed * dt;
		movesy(character);
	}
	//right :
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		moving.y += speed * dt;
		movesy(character);
	}


	

	animation.update(row, dt, faceleft);
	character.setTextureRect(animation.uvrect);
	character.move(moving);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(character);
}

sf::Vector2f Player::position()
{
	sf::Vector2f pos = character.getPosition();
	return pos;
}

sf::Vector2f Player::size()
{
	sf::Vector2f size = character.getSize();
	return size;
}

bool Player::collision(sf::RectangleShape enemy)
{
	if (character.getGlobalBounds().intersects(enemy.getGlobalBounds()))
		return true;
	else
		return false;
}

bool Player::collision1(sf::Sprite enemy) {
	if (character.getGlobalBounds().intersects(enemy.getGlobalBounds()))
		return true;
	else
		return false;
}