#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float shiftTime, float speed, float jumpHeight,sf::Vector2f size) :
	animation(texture, imageCount, shiftTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;

	body.setSize(size);
	body.setPosition(510.0f, 102.0f);
	body.setTexture(texture);
	body.setOrigin(50.0f, 50.0f);

	row = 0;
	faceRight = true;
}



void Player::update(float deltaTime)
{
	velocity.x = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;//
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += speed;//
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)))
		velocity.x += 2 * speed;//
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)|| sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)))
		velocity.x -= 2 * speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))) {// && canJump
		velocity.y = -sqrtf(4.0f * 981.0f * jumpHeight);//9.81 actual gravity but in sense of pixels lets take 981
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump ){// && canJump
			
			canJump = false;
			velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);//9.81 actual gravity but in sense of pixels lets take 981
	}
	velocity.y += 981.0f*deltaTime;
	
	if (velocity.x == 0.0f) {
		row=0;
	}
	else {
		row = 1;
		
		if (velocity.x > 0) {
			faceRight = true;
		}
		else {
			faceRight = false;
		}
	}
	animation.update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvGrid);
	body.move(velocity*deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

sf::Vector2f Player::getPosition()
{
	return body.getPosition();
}

void Player::onCollision(sf::Vector2f direction)
{ 
	//canJump = true;

	if (direction.x < 0.0f){
		velocity.x = 0.0f;//Collision on left
	
	}else if(direction.x > 0.0f) {
		velocity.x = 0.0f;//Collision on right
		
	}


	if (direction.y < 0.0f) {
		
		velocity.y = 0.0f; //Collision on bottom
	}
	else if (direction.y > 0.0f) {
		canJump = true;
		velocity.y = 0.0f;

	}
}

