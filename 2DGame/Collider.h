#pragma once
#include<SFML/Graphics.hpp>
class Collider
{
public:
	Collider(sf::RectangleShape& body);

	bool checkCollision(Collider&& other,sf::Vector2f& direction, float recoil);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f;	}

	void Move(float x, float y) { body.move(x, y); }

private:
	sf::RectangleShape& body; 
};

