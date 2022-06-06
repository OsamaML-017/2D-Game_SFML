#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float shiftTime) {
	this->imageCount = imageCount;
	this->shiftTime = shiftTime;

	sf::Vector2u textureSize=texture->getSize();
	uvGrid.width = textureSize.x/ float(imageCount.x);
	uvGrid.height = textureSize.y / float(imageCount.y);

	totalTime = 0.0f;
	currentCell.x = 0;

}

void Animation::update(int row, float deltaTime,bool faceRight) {
	currentCell.y = row;
	totalTime += deltaTime;
	if (totalTime >= shiftTime) {
		totalTime -= shiftTime;
		currentCell.x++;
		if (currentCell.x >= imageCount.x)
		{
			currentCell.x = 0;
		}
	}
	
	uvGrid.top = uvGrid.height * currentCell.y;
	if (faceRight) {
		uvGrid.left = abs(uvGrid.width) * currentCell.x;
		uvGrid.width = abs(uvGrid.width);
	}
	else {
		uvGrid.left = abs(uvGrid.width) * (currentCell.x+1);
		uvGrid.width = -abs(uvGrid.width);
	}
}
