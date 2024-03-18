
#include "Animation.h"



Animation::Animation(sf::Texture* texture, sf::Vector2u imagecount, float switchtime) 
{
	this->imagecount = imagecount;
	this->switchtime = switchtime;
	totaltime = 0.0f;
	current.x = 0;

	
	uvrect.width  = texture->getSize().x / float(imagecount.x);
	uvrect.height = texture->getSize().y / float(imagecount.y);
}

void Animation::update(int row, float dt , bool faceleft)
{
	current.y = row;
	totaltime += dt;

	if (totaltime >= switchtime) 
	{
		totaltime -= switchtime;
		current.x++;

		if (current.x >= imagecount.x) 
		{
			current.x = 0;
		}
	}
	
	if (faceleft)
	{
		uvrect.left = current.x * uvrect.width;
		uvrect.width = abs(uvrect.width);
	}
	else
	{
		uvrect.left = (current.x + 1 )* abs(uvrect.width);
		uvrect.width = -abs(uvrect.width);
	}
	uvrect.top = current.y * uvrect.height;

}