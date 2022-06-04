#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"Collider.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float shiftTime,float speed,float jumpHeight,sf::Vector2f size);

	void update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	void onCollision(sf::Vector2f direction);
	bool getCanJump() { return canJump; }
	void setCanJump() { canJump = true; }
	Collider GetCollider() { return Collider(body); }
private:
	
	sf::RectangleShape body;
	Animation animation;
	
	float speed;
	float deltaTime;
	int row;
	bool faceRight;
	
	bool canJump=true;
	sf::Vector2f velocity;
	float jumpHeight;
};

