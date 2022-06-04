#include "Menu.h"

Menu::Menu(float width, float height) {
	if (!font.loadFromFile("Font/alexandria.ttf"))
		std::cout << "Could not load the font!" << std::endl;
	
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::White);
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setString("Play");
	mainMenu[0].setPosition(400, 200);

	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::White);
	mainMenu[1].setCharacterSize(70);
	mainMenu[1].setString("Settings");
	mainMenu[1].setPosition(400, 300);
	
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::White);
	mainMenu[2].setCharacterSize(70);
	mainMenu[2].setString("Exit");
	mainMenu[2].setPosition(400, 400);

	mainMenuSelected = -1;
}

Menu::~Menu(){ 

}

void Menu::Draw(sf::RenderWindow& window){
	for (int i = 0; i < MaxMenuCount; ++i) {
		window.draw(mainMenu[i]);
	}
}

void Menu::moveUp() {
	if (mainMenuSelected - 1 >= 0) {
		mainMenu[mainMenuSelected].setFillColor(sf::Color::White);
		mainMenuSelected--;
		
		if (mainMenuSelected == -1) {
			mainMenuSelected = 2;
		}
		mainMenu[mainMenuSelected].setFillColor(sf::Color::Yellow);
	}
}

void Menu::moveDown() {
	if (mainMenuSelected + 1 <= MaxMenuCount) {
		mainMenu[mainMenuSelected].setFillColor(sf::Color::White);
		mainMenuSelected++;
		
		if (mainMenuSelected == MaxMenuCount) {
			mainMenuSelected = 0;
		}
		mainMenu[mainMenuSelected].setFillColor(sf::Color::Yellow);
	}
}