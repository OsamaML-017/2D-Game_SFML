#include "GameFunc.h"
#include<stdio.h>

void Resize(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = (float)window.getSize().x / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void PlayGame()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Tutorial", sf::Style::Default);

	sf::Texture playerTexture;
	sf::Texture wallTexture;
	sf::Texture obstacleTex;
	sf::Texture obstacleTex1;

	wallTexture.loadFromFile("Textures/Wall.jpg");
	obstacleTex.loadFromFile("Textures/obstacle2.jpg");
	obstacleTex1.loadFromFile("Textures/obstacle1.jpg");

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Textures/background.jpg");

	sf::Sprite sprite(backgroundTexture);
	sprite.setOrigin(sf::Vector2f(((float)window.getSize().x) / 2, (float(window.getSize().y)) / 2 + 200.0f));
	sprite.setScale(1, 0.7);

	playerTexture.loadFromFile("Textures/Linux.png");
	Player player(&playerTexture, sf::Vector2u(3, 9), 0.2f, 100.0f, 210.0f, sf::Vector2f(100.0f, 100.0f));

	std::vector<Tilemap> tilemaps;
	std::vector<Obstacles> obstacles;

	for (int i = 1; i <= 3; i++) {
		tilemaps.push_back(Tilemap(&wallTexture, sf::Vector2f(500, 400.0f), sf::Vector2f(i * 500.0f, 500.0f)));
	}
	obstacles.push_back(Obstacles(&obstacleTex, sf::Vector2f(140, 200), sf::Vector2f(700, 200), true));
	obstacles.push_back(Obstacles(&obstacleTex1, sf::Vector2f(150, 410), sf::Vector2f(1050, 200), false));

	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

	float deltaTime = 0.0f;
	sf::Clock clock;
	while (window.isOpen()) {

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
				Resize(window, view);
				break;
			case sf::Event::KeyReleased:
				if (evnt.key.code == sf::Keyboard::Key::Escape) {
					PauseScreen(window);
				}
			}
		}

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

		view.setCenter(player.getPosition());
		window.clear();
		sprite.setPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y));

		window.draw(sprite);
		window.setView(view);

		player.Draw(window);
		for (Tilemap& tilemap : tilemaps)
			tilemap.Draw(window);
		for (Obstacles& obstacle : obstacles)
			obstacle.Draw(window);
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
			}
		}
		Options.clear();
		Options.draw(settings);
		Options.display();
	}
}

void PauseScreen(sf::RenderWindow& win) {
	sf::Text pause;
	sf::Font font;
	font.loadFromFile("C:/Users/osama/source/repos/2DGame/2DGame/Font/alexandria.ttf");
	pause.setCharacterSize(70);
	pause.setString("Continue");
	pause.setFont(font);
	pause.setFillColor(sf::Color::Yellow);
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
		}
		
		win.clear();
		win.draw(pause);
		win.display();
	}
}