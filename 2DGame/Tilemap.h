#pragma once
#include<SFML/Graphics.hpp>
#include"Collider.h"

class Tilemap
{
public:
	Tilemap(sf::Texture* texture,sf::Vector2f size,sf::Vector2f position);

	void Draw(sf::RenderWindow& window) { window.draw(body); }

	Collider GetCollider() { return Collider(body); }
private:
	sf::RectangleShape body;
};

