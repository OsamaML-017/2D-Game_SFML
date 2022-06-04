#include "Collider.h"
#include<iostream>

Collider::Collider(sf::RectangleShape& body):body(body)
{
}

bool Collider::checkCollision(Collider&& other, sf::Vector2f& direction,float recoil)
{
	sf::Vector2f thisCenter=GetHalfSize();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f otherCenter = other.GetHalfSize();
	sf::Vector2f otherPosition = other.GetPosition();

	float deltaX = otherPosition.x-thisPosition.x;
	float deltaY = otherPosition.y-thisPosition.y;

	float intersectX = abs(deltaX) - (thisCenter.x + otherCenter.x);
	float intersectY = abs(deltaY) - (thisCenter.y + otherCenter.y);

	if (intersectX < 0.0f && intersectY < 0.0f) {
			
		recoil=std::min(std::max(recoil,0.0f),1.0f);
		
		if (intersectX > intersectY) {
			if (deltaX > 0.0f) {
				Move(intersectX * (1.0f-recoil), 0.0f);// try only this line in this if statement without recoil should be fun
				other.Move(-intersectX*recoil,0.0f);
				
				direction.x = -1.0f;
				direction.y = 0.0f;
			}
			else {
				Move(-intersectX * (1.0f-recoil), 0.0f);// try only this line in this if statement without recoil should be fun
				other.Move(intersectX * recoil, 0.0f);
				
				direction.x = 1.0f;
				direction.y = 0.0f;
			}
		}
		else {
			if (deltaY > 0.0f) {
				Move(0.0f,intersectY * (1.0f-recoil));// try only this line in this if statement without recoil should be fun
				other.Move(0.0f,-intersectY * recoil);

				direction.x = 0.0f;
				direction.y = -1.0f;
			}
			else {
				Move(0.0f,-intersectY * (1.0f-recoil));// try only this line in this if statement without recoil should be fun
				other.Move(0.0f,intersectY * recoil);

				direction.x = 0.0f;
				direction.y = 1.0f;
			}
		}
			return true;
	}
	return false;
}
