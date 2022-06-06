#include "GameFunc.h"
#include<stdio.h>

void Resize(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = (float)window.getSize().x / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void PlayGame()
{
	//Creating a Window
	bool count = true;
	sf::RenderWindow window(sf::VideoMode(1280, 801), "SFML Tutorial", sf::Style::Default);
	
	//Making and Loading necessery textures

	sf::Texture playerTexture;
	sf::Texture wallTexture;
	sf::Texture obstacleTex;
	sf::Texture obstacleTex1;
	
	sf::Texture trapTexture1;
//	sf::Texture trapTexture2;
	sf::Texture trapTexture3;
	sf::Texture trapTexture4;

	wallTexture.loadFromFile("Textures/Wall.jpg");
	obstacleTex.loadFromFile("Textures/obstacle2.jpg");
	obstacleTex1.loadFromFile("Textures/obstacle1.jpg");
	
	trapTexture1.loadFromFile("Textures/metal_Killer.png");
	//trapTexture2.loadFromFile("Textures/wood_Killer.png");
	trapTexture3.loadFromFile("Textures/Fire.png");
	trapTexture4.loadFromFile("Textures/Lightning.png");

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Textures/background.jpg");

	sf::Sprite sprite(backgroundTexture);
	sprite.setOrigin(sf::Vector2f(((float)window.getSize().x) / 2, (float(window.getSize().y)) / 2 + 200.0f));
	sprite.setScale(1, 0.7);

	playerTexture.loadFromFile("Textures/Linux.png");
	Player player(&playerTexture, sf::Vector2u(3, 9), 0.2f, 100.0f, 210.0f, sf::Vector2f(100.0f, 100.0f));

	std::vector<Tilemap> tilemaps;
	std::vector<Obstacles> obstacles;
	std::vector<Traps> traps;

	for (int i = 1; i <= 10; i++) {
		tilemaps.push_back(Tilemap(&wallTexture, sf::Vector2f(500, 400.0f), sf::Vector2f(i * 500.0f, 500.0f)));
	}
	//Test Objects/Obstacles
	// 
	//Pushable Obstacles
	obstacles.push_back(Obstacles(&obstacleTex, sf::Vector2f(140, 200), sf::Vector2f(700, 200), true));
	
	//Rigid Obstacles
	obstacles.push_back(Obstacles(&obstacleTex1, sf::Vector2f(150, 340), sf::Vector2f(1050, 200), false));
	
	//Damage dealers
	traps.push_back(Traps(&trapTexture1, sf::Vector2u(4, 1), sf::Vector2f(1400.0f, 250.0f), sf::Vector2f(50.0f, 100.0f), 0.3));
	//traps.push_back(Traps(&trapTexture2, sf::Vector2u(4, 1), sf::Vector2f(1270.0f, 160.0f), sf::Vector2f(50.0f, 150.0f), 0.3));
	traps.push_back(Traps(&trapTexture3, sf::Vector2u(6, 1), sf::Vector2f(1850.0f, 240.0f), sf::Vector2f(90.0f, 120.0f), 0.3));
	traps.push_back(Traps(&trapTexture4, sf::Vector2u(21, 1), sf::Vector2f(2020.0f, 100.0f), sf::Vector2f(70.0f, 250.0f), 0.3));



	//Creating a View
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

	float deltaTime = 0.0f;
	sf::Clock clock;
	while (window.isOpen()&&count) {

		sf::Event evnt;
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f) {
			deltaTime = 1.0f / 20.0f;
		}
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				std::cout << "Height: "<<window.getSize().y<<std::endl;
				Resize(window, view);
				break;
			case sf::Event::KeyReleased:
				if (evnt.key.code == sf::Keyboard::Key::Escape) {
					PauseScreen(window,player);
				}
			}
		}

		for (Traps& trap : traps) 
			trap.updateTrap(0,deltaTime,true);
		
		player.update(deltaTime);
		sf::Vector2f direction;

		for (Tilemap& tilemap : tilemaps) {
			if (tilemap.GetCollider().checkCollision(player.GetCollider(), direction, 1.0f))
				player.onCollision(direction);
			for (Obstacles& obstacle : obstacles)
				tilemap.GetCollider().checkCollision(obstacle.GetCollider(), direction, 1.0f);
		}
		sf::Vector2f direction1;

		for (Obstacles& obstacle : obstacles) {

			if (obstacle.isPushable()) {
				if (obstacle.GetCollider().checkCollision(player.GetCollider(), direction1, 0.7f)) {
					player.onCollision(direction1);
				}
			}
			else {
				obstacle.GetCollider().checkCollision(player.GetCollider(), direction1, 1.0f);
				player.onCollision(direction1);
			}
		}
		sf::Vector2f direction2;
		for (Traps& trap : traps) {
			if (trap.getCollider().checkCollision(player.GetCollider(), direction2, 1.0f)) {
				GameOver(window,player);
				count = false;
			}
		}

		view.setCenter(player.getPosition());
		window.clear();
		sprite.setPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y+100));

		window.draw(sprite);
		window.setView(view);

		player.Draw(window);
		for (Tilemap& tilemap : tilemaps)
			tilemap.Draw(window);
		for (Obstacles& obstacle : obstacles)
			obstacle.Draw(window);
		for (Traps& trap : traps) 
			trap.Draw(window);

		
		window.display();
	}


}

void dummyOptions() {
	sf::RenderWindow Options(sf::VideoMode(960, 720), "Options", sf::Style::Default);
	
	//Setting Background
	sf::RectangleShape settings;
	settings.setSize(sf::Vector2f(960, 720));
	sf::Texture settingsTexture;
	settingsTexture.loadFromFile("Textures/Settings.png");
	settings.setTexture(&settingsTexture);

	while (Options.isOpen()) {

	

		sf::Event e2;
		while (Options.pollEvent(e2)) {
			switch (e2.type) {
			case sf::Event::Closed:
				Options.close();
			case sf::Event::KeyReleased:
				if (e2.key.code == sf::Keyboard::Key::Escape) {
					Options.close();
				}
			}
		}
		Options.clear();
		Options.draw(settings);
		Options.display();
	}
}


void PauseScreen(sf::RenderWindow& win, Player& player) {
	//Background Image
	sf::RectangleShape background;
	//background.setSize(sf::Vector2f(1280, 720));
	sf::Texture backgroundTexture;
	background.setOrigin(sf::Vector2f(player.getPosition().x / 2, player.getPosition().y / 2));
	backgroundTexture.loadFromFile("Textures/Menue_Background.jpg");
	background.setTexture(&backgroundTexture);


	//Text
	sf::Text pause;
	sf::Font font;
	font.loadFromFile("C:/Users/osama/source/repos/2DGame/2DGame/Font/alexandria.ttf");

	pause.setFont(font);
	pause.setCharacterSize(70);
	pause.setString("Continue");
	pause.setFillColor(sf::Color::Yellow);
	pause.setPosition(player.getPosition().x -90, player.getPosition().y );
	//view.setCenter(win.getSize().x / 2, win.getSize().y / 2);

	while (win.isOpen() && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))) {
		sf::Event ep;
		while (win.pollEvent(ep)) {
			switch (ep.type) {
			case sf::Event::Closed:
				win.close();
				break;
			case sf::Event::KeyReleased:
				if (ep.key.code == sf::Keyboard::Key::Return) {
					return;
				}

			}

			win.clear(sf::Color(150,155,155));
			win.draw(background);
			win.draw(pause);
			win.display();
		}
	}
}


void GameOver(sf::RenderWindow& window,Player& player) {
	sf::Text over;
	sf::Font font;
	font.loadFromFile("C:/Users/osama/source/repos/2DGame/2DGame/Font/alexandria.ttf");
		 
	over.setFont(font);
	over.setCharacterSize(70);
	over.setString("Game Over");
	over.setFillColor(sf::Color::Yellow);
	over.setPosition(player.getPosition().x-90,player.getPosition().y-170);
	
	float deltaTime = 0.0f;

	sf::Clock clock;

	while (window.isOpen() && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))) {
		
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f) {
			deltaTime = 1.0f / 20.0f;
		}

		sf::Event ep;
		while (window.pollEvent(ep)) {
			switch (ep.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased:
				if (ep.key.code == sf::Keyboard::Key::Return) {
					return;
				}
			
			}
		}

		//window.clear();
		player.deathUpdate(8,deltaTime);
		window.clear(sf::Color(150, 155, 155));
		window.draw(over);
		player.Draw(window);
		window.display();
	}
}