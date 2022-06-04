#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include"Menu.h"
#include"GameFunc.h"




int main() {
	sf::RenderWindow MENU(sf::VideoMode(960, 720), "Main Menue", sf::Style::Default);
	Menu mainMenu(MENU.getSize().x,MENU.getSize().y);
	
	// Setting Background
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(960, 720));
	sf::Texture backgroundTexture;

	backgroundTexture.loadFromFile("Textures/Menue_Background.jpg");
	background.setTexture(&backgroundTexture);


	while (MENU.isOpen()) {
		sf::Event e1;
		while (MENU.pollEvent(e1)) {
			
			switch (e1.type) {

			case sf::Event::Closed:
				MENU.close();
				
			case sf::Event::KeyReleased:
				if(e1.key.code==sf::Keyboard::Up || e1.key.code == sf::Keyboard::W)
				{
					mainMenu.moveUp();
					break;
				}
				else if (e1.key.code == sf::Keyboard::Down || e1.key.code == sf::Keyboard::S) {
					mainMenu.moveDown();
					break;
				}
				else if (e1.key.code==sf::Keyboard::Return) {

					int x = mainMenu.mainMenuPressed();
					if (x == 0) {
						PlayGame();
					}
					else if (x == 1) {
						dummyOptions();
					}
					else if (x == 2) {
						MENU.close();
					}
				}
			}
		}
		MENU.clear();
		MENU.draw(background);
		mainMenu.Draw(MENU);
		MENU.display();
	}
	return 0;
}
