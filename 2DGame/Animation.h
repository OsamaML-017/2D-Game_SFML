#pragma once
#include<SFML/Graphics.hpp>
class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float shiftTime);

	void update(int row, float deltaTime,bool faceRight);

private:
	sf::Vector2u currentCell;
	sf::Vector2u imageCount;

	float totalTime;
	float shiftTime;
public:
	sf::IntRect uvGrid;
};

