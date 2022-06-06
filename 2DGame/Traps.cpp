#include "Traps.h"

Traps::Traps(sf::Texture* tex, sf::Vector2u imageCount, sf::Vector2f position, sf::Vector2f size, float shiftTime):
	 trapAnimation(tex,imageCount,shiftTime)
{
	body.setSize(size);
	body.setTexture(tex);
	body.setPosition(position);
	body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
	row = 0;
	faceRight = true;
}

Traps::~Traps()
{
}

void Traps::updateTrap(int row, float deltaTime, bool faceRight)
{
	trapAnimation.update(row,deltaTime,faceRight);
	body.setTextureRect(trapAnimation.uvGrid);
}

