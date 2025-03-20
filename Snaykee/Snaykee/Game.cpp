#include "Game.h"
#include "MTigerCore_Math/MR_Math.h"

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

	this->score += this->_deltaTime;

	// Calculations
	this->GenerateObstacles();
	this->CheckObstacleCollisions();

	// Updating
	this->_player.Update(fDeltaTime);

	for (Obstacle& ob : this->_obstacles) // Update obstacles
		ob.Update(fDeltaTime);
}

void Game::Draw(sf::RenderWindow& window)
{
	this->_player.Draw(window);

	for (Obstacle& ob : this->_obstacles) // Draw obstacles
		ob.Draw(window);
}

void Game::GenerateObstacles()
{
	int rn = MR_Math::RandomInt(100);

	if (rn > 10)
		return;

	float randSize = MR_Math::RandomFloatRange(5.0f, 10.0f);
	float randPosX = MR_Math::RandomFloatRange(30.0f, 1170.0f);
	float randPosY = MR_Math::RandomFloat(30.0f);
	float randSpeed = MR_Math::RandomFloat(1.0f);

	Obstacle ob({ randSize, randSize }, { randPosX, randPosY }, randSpeed);
	this->_obstacles.push_back(ob);
}

void Game::CheckObstacleCollisions()
{
	Collider_SFML playerCollider = this->_player.Get_Gollider();

	for (Obstacle& ob : this->_obstacles)
	{
		if (ob.Get_Collider().CheckCollision(playerCollider, 1.0f))
			this->Execute_GameOver();
	}
}

void Game::Execute_GameOver()
{
	std::cout << "GAME OVER!!! [Score: " << this->score << "]\n";
}