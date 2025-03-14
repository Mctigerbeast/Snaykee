#include "Game.h"

Game::Game(std::string gameTitle)
	: _gameTitle(gameTitle)
{
	this->_playertexture = new sf::Texture;
	_playertexture->loadFromFile("Resources/SpriteSheet_Example.png");

	this->_player = Player_TopDown_SFML(_playertexture, sf::Vector2u({ 8, 4 }), 0.1f, 500.0f);
	this->_player.SetupAnimation(1, 2, 3, 0);
}

Game::~Game()
{
	delete this->_playertexture;
}

void Game::Tick(float fDeltaTime)
{
	this->_deltaTime = fDeltaTime;

	this->_player.Update(fDeltaTime);
}

void Game::Draw(sf::RenderWindow& window)
{
	this->_player.Draw(window);
}