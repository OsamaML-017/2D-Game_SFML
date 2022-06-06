#pragma once
#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<time.h>
#include<vector>
#include"Player.h"
#include"Tilemap.h"
#include"Traps.h"
#include"Obstacles.h"

static const float VIEW_HEIGHT = 512.0f;

void Resize(const sf::RenderWindow& window, sf::View& view);

//Main Game Function

void PlayGame();
void PauseScreen(sf::RenderWindow& win,Player& player);
void GameOver(sf::RenderWindow& window,Player& player);
void dummyOptions();

