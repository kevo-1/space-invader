#include <SFML/Graphics.hpp>
class Animation
{
public:
	Animation(sf::Texture* texture , sf::Vector2u imagecount , float switchtime);


	void update(int row, float dt , bool faceleft);

	

public:
	sf::IntRect uvrect;



private:
	sf::Vector2u imagecount;
	sf::Vector2u current;

	float totaltime;
	float switchtime;
};
