#include "Obstacles.h"

Obstacles::Obstacles(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position,bool pushable)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
	
	this->pushable = pushable;
}
