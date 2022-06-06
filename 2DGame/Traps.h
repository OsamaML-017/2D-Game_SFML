#pragma once
#include<SFML/Graphics.hpp>
#include"Collider.h"
#include"Animation.h"

class Traps
{
public:
	Traps(sf::Texture* tex, sf::Vector2u imageCount, sf::Vector2f position, sf::Vector2f size, float shiftTime);
	~Traps();

	void Draw(sf::RenderWindow& window) {
		window.draw(body);
	}
	void updateTrap(int row,float deltaTime,bool faceRight);
	Collider getCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	Animation trapAnimation;
	//float speed;
	float deltaTime;
	int row;
	bool faceRight;

};

