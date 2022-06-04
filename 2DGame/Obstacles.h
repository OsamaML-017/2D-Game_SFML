#pragma once
#include<SFML/Graphics.hpp>
#include"Collider.h"

class Obstacles
{
public:
	Obstacles(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position,bool pushable);

	void Draw(sf::RenderWindow& window) { window.draw(body); }
	bool isPushable() { return pushable; }
	Collider GetCollider() { return Collider(body); }
private:
	sf::RectangleShape body;
	bool pushable;
};

