#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>

constexpr auto MaxMenuCount = 3;;

class Menu
{
public:
	Menu(float height, float width);

	void Draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();

	int mainMenuPressed() {
		return mainMenuSelected;
	}
	~Menu();
private:
	int mainMenuSelected;
	
	sf::Font font;
	sf::Text mainMenu[MaxMenuCount];
};

